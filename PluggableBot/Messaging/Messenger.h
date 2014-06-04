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
		 * Posłaniec, czy też szyna wiadomości, który synchronizuje dostęp do głównego elementu
		 * komunikacyjnego aplikacji.
		 *
		 * Klasa ta odpowiada za przekazywanie wiadomości między poszczególnymi podsystemami
		 * aplikacji, ze szczególnym uwzględnieniem tych działających na różnych wątkach
		 * (np. głównego wątku aplikacji i wątków obsługujących wtyczki czy wiadomości
		 * asynchroniczne).
		 * Do synchronizacji dostępu do listy używana jest sekcja krytyczna, ponieważ każda
		 * z metod wymaga wyłącznego dostępu. Jest to miejsce na ulepszenia, gdyż Get tak naprawdę
		 * opiera się głównie na odczycie(i sprawdzeniu, czy dana wiadomość istnieje), ale ponieważ
		 * szukamy konkretnego typu wiadomości, musielibyśmy wykonać double-checking, co niekoniecznie
		 * musi pomóc, a na pewno skomplikuje implementacje.
		 * Dodatkowo używane jest zdarzenie, by powiadomić wątki oczekujące na wiadomości, że takowe
		 * nadeszły.
		 *
		 * Kolejność wiadomości nie jest zachowana. Funkcje Get mogą zmieniać kolejność wiadomości
		 * na liście, by przyspieszyć usuwanie elementu(zastępowany jest ostatnim, zamiast przesunięcia
		 * wszystkich elementów).
		 *
		 * Problemy z implementacją:
		 * Przez użycie smart pointerów i szablonów, biblioteki DLL muszą być kompilowane z tą samą
		 * implementacją CRT(czyli tak naprawdę w konkretnej wersji Visual Studio).
		 *
		 * \sa
		 * \ref pages_messenger_description
		 */
		class PLUGIN_API Messenger
		{
		public:
			/**
			 * Inicjalizuje nowy obiekt.
			 */
			Messenger();

			/**
			 * Czyści po obiekcie.
			 */
			~Messenger();

			/**
			 * Wysyła nową pustą wiadomość o wskazanym typie.
			 *
			 * UWAGA! Może spowodować problem z dealokacją w niewłaściwym miejscu(DLL boundary)
			 */
			template<typename TMessage>
			void Send()
			{
				this->Send(MessagePointer(new TMessage(), MessageDeleter<TMessage>()));
			}

			/**
			 * Wysyła wskazaną wiadomość, opakowując obiekt w shared_ptr.
			 */
			template<typename TMessage>
			void Send(TMessage* message)
			{
				this->Send(MessagePointer(message));
			}

			/**
			 * Wysyła wskazaną wiadomość.
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
			 * Pobiera jedną wiadomość z list, a jeśli takowa nie istnieje - czeka aż się pojawi
			 * i ją zwraca. Jeśli czas oczekiwania zostanie przekroczony, zostaje zwrócony nullptr.
			 *
			 * \param type Typ wiadomości, której oczekujemy.
			 * \param timeout Maksymalny czas oczekiwania. Domyślnie nieskończoność.
			 */
			MessagePointer Get(int type, DWORD timeout = INFINITE);

			/**
			 * Wybiera z listy wiadomości, które spełniają wskazany warunek. Gdy nie ma wiadomości
			 * spełniających takie założenia, czeka określony czas do pojawienia się PIERWSZEJ
			 * wiadomości, która może być zwrócona. Gdy czas oczekiwania zostanie przekroczony,
			 * zostanie zwrócona pusta kolekcja wiadomości.
			 *
			 * \param predicate Warunek, który musi zostać spełniony, by wiadomość była zwrócona.
			 * \param timeout Maksymalny czas oczekiwania. Domyślnie nieskończoność.
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