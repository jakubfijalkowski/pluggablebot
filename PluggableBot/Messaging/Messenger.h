#pragma once
#include <memory>
#include <list>
#include <vector>
#include <functional>
#include <Windows.h>
#include "../Config.h"
#include "IMessage.h"
#include "../Logging/LogFactory.h"

namespace PluggableBot
{
	namespace Messaging
	{

		typedef std::function<bool(IMessage*)> MessagePredicate;
		typedef std::list<MessagePointer> MessageList;
		typedef std::shared_ptr<MessageList> MessageListPointer;

		/**
		 * Pos³aniec, czy te¿ szyna wiadomoœci, który synchronizuje dostêp do g³ównego elementu
		 * komunikacyjnego aplikacji.
		 *
		 * Klasa ta odpowiada za przekazywanie wiadomoœci miêdzy poszczególnymi podsystemami
		 * aplikacji, ze szczególnym uwzglêdnieniem tych dzia³aj¹cych na ró¿nych w¹tkach
		 * (np. g³ównego w¹tku aplikacji i w¹tków obs³uguj¹cych wtyczki czy wiadomoœci
		 * asynchroniczne).
		 * Do synchronizacji dostêpu do listy u¿ywana jest sekcja krytyczna, poniewa¿ ka¿da
		 * z metod wymaga wy³¹cznego dostêpu. Jest to miejsce na ulepszenia, gdy¿ Get tak naprawdê
		 * opiera siê g³ównie na odczycie(i sprawdzeniu, czy dana wiadomoœæ istnieje), ale poniewa¿
		 * szukamy konkretnego typu wiadomoœci, musielibyœmy wykonaæ double-checking, co niekoniecznie
		 * musi pomóc, a na pewno skomplikuje implementacje.
		 * Dodatkowo u¿ywane jest zdarzenie, by powiadomiæ w¹tki oczekuj¹ce na wiadomoœci, ¿e takowe
		 * nadesz³y.
		 *
		 * Kolejnoœæ wiadomoœci nie jest zachowana. Funkcje Get mog¹ zmieniaæ kolejnoœæ wiadomoœci
		 * na liœcie, by przyspieszyæ usuwanie elementu(zastêpowany jest ostatnim, zamiast przesuniêcia
		 * wszystkich elementów).
		 *
		 * Problemy z implementacj¹:
		 * Przez u¿ycie smart pointerów i szablonów, biblioteki DLL musz¹ byæ kompilowane z t¹ sam¹
		 * implementacj¹ CRT(czyli tak naprawdê w konkretnej wersji Visual Studio).
		 */
		class PLUGIN_API Messenger
		{
		public:
			/**
			 * Inicjalizuje nowy obiekt.
			 */
			Messenger();

			/**
			 * Czyœci po obiekcie.
			 */
			~Messenger();

			/**
			 * Wysy³a now¹ pust¹ wiadomoœæ o wskazanym typie.
			 *
			 * UWAGA! Mo¿e spowodowaæ problem z dealokacj¹ w niew³aœciwym miejscu(DLL boundary)
			 */
			template<typename TMessage>
			void Send()
			{
				this->Send(MessagePointer(new TMessage(), MessageDeleter<TMessage>()));
			}

			/**
			 * Wysy³a wskazan¹ wiadomoœæ, opakowuj¹c obiekt w shared_ptr.
			 */
			template<typename TMessage>
			void Send(TMessage* message)
			{
				this->Send(MessagePointer(message));
			}

			/**
			 * Wysy³a wskazan¹ wiadomoœæ.
			 */
			void Send(MessagePointer message);

			/**
			 * Badziej przejrzysta wersja Get(type, 0);
			 */
			MessagePointer TryGet(int type)
			{
				return this->Get(type, 0);
			}

			/**
			 * Badziej przejrzysta wersja Get(predicate, 0);
			 */
			MessageListPointer TryGet(MessagePredicate predicate)
			{
				return this->Get(predicate, 0);
			}

			/**
			 * Pobiera jedn¹ wiadomoœæ z list, a jeœli takowa nie istnieje - czeka a¿ siê pojawi
			 * i j¹ zwraca. Jeœli czas oczekiwania zostanie przekroczony, zostaje zwrócony nullptr.
			 *
			 * \param type Typ wiadomoœci, której oczekujemy.
			 * \param timeout Maksymalny czas oczekiwania. Domyœlnie nieskoñczonoœæ.
			 */
			MessagePointer Get(int type, DWORD timeout = INFINITE);

			/**
			 * Wybiera z listy wiadomoœci, które spe³niaj¹ wskazany warunek. Gdy nie ma wiadomoœci
			 * spe³niaj¹cych takie za³o¿enia, czeka okreœlony czas do pojawienia siê PIERWSZEJ
			 * wiadomoœci, która mo¿e byæ zwrócona. Gdy czas oczekiwania zostanie przekroczony,
			 * zostanie zwrócona pusta kolekcja wiadomoœci.
			 *
			 * \param predicate Warunek, który musi zostaæ spe³niony, by wiadomoœæ by³a zwrócona.
			 * \param timeout Maksymalny czas oczekiwania. Domyœlnie nieskoñczonoœæ.
			 */
			MessageListPointer Get(MessagePredicate predicate, DWORD timeout = INFINITE);

		private:
			void Get(MessagePredicate predicatem, DWORD timeout, MessageListPointer output);
			bool WaitForNewObject(DWORD timeout);

			const Logging::LoggerPointer Logger;

			std::vector<MessagePointer> messages;

			CRITICAL_SECTION lock;
			HANDLE newMessageEvent;
			volatile long waitCount;
		};
	}
}