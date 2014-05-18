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
		 * Pos�aniec, czy te� szyna wiadomo�ci, kt�ry synchronizuje dost�p do g��wnego elementu
		 * komunikacyjnego aplikacji.
		 *
		 * Klasa ta odpowiada za przekazywanie wiadomo�ci mi�dzy poszczeg�lnymi podsystemami
		 * aplikacji, ze szczeg�lnym uwzgl�dnieniem tych dzia�aj�cych na r�nych w�tkach
		 * (np. g��wnego w�tku aplikacji i w�tk�w obs�uguj�cych wtyczki czy wiadomo�ci
		 * asynchroniczne).
		 * Do synchronizacji dost�pu do listy u�ywana jest sekcja krytyczna, poniewa� ka�da
		 * z metod wymaga wy��cznego dost�pu. Jest to miejsce na ulepszenia, gdy� Get tak naprawd�
		 * opiera si� g��wnie na odczycie(i sprawdzeniu, czy dana wiadomo�� istnieje), ale poniewa�
		 * szukamy konkretnego typu wiadomo�ci, musieliby�my wykona� double-checking, co niekoniecznie
		 * musi pom�c, a na pewno skomplikuje implementacje.
		 * Dodatkowo u�ywane jest zdarzenie, by powiadomi� w�tki oczekuj�ce na wiadomo�ci, �e takowe
		 * nadesz�y.
		 *
		 * Kolejno�� wiadomo�ci nie jest zachowana. Funkcje Get mog� zmienia� kolejno�� wiadomo�ci
		 * na li�cie, by przyspieszy� usuwanie elementu(zast�powany jest ostatnim, zamiast przesuni�cia
		 * wszystkich element�w).
		 *
		 * Problemy z implementacj�:
		 * Przez u�ycie smart pointer�w i szablon�w, biblioteki DLL musz� by� kompilowane z t� sam�
		 * implementacj� CRT(czyli tak naprawd� w konkretnej wersji Visual Studio).
		 */
		class PLUGIN_API Messenger
		{
		public:
			/**
			 * Inicjalizuje nowy obiekt.
			 */
			Messenger();

			/**
			 * Czy�ci po obiekcie.
			 */
			~Messenger();

			/**
			 * Wysy�a now� pust� wiadomo�� o wskazanym typie.
			 *
			 * UWAGA! Mo�e spowodowa� problem z dealokacj� w niew�a�ciwym miejscu(DLL boundary)
			 */
			template<typename TMessage>
			void Send()
			{
				this->Send(MessagePointer(new TMessage(), MessageDeleter<TMessage>()));
			}

			/**
			 * Wysy�a wskazan� wiadomo��, opakowuj�c obiekt w shared_ptr.
			 */
			template<typename TMessage>
			void Send(TMessage* message)
			{
				this->Send(MessagePointer(message));
			}

			/**
			 * Wysy�a wskazan� wiadomo��.
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
			 * Pobiera jedn� wiadomo�� z list, a je�li takowa nie istnieje - czeka a� si� pojawi
			 * i j� zwraca. Je�li czas oczekiwania zostanie przekroczony, zostaje zwr�cony nullptr.
			 *
			 * \param type Typ wiadomo�ci, kt�rej oczekujemy.
			 * \param timeout Maksymalny czas oczekiwania. Domy�lnie niesko�czono��.
			 */
			MessagePointer Get(int type, DWORD timeout = INFINITE);

			/**
			 * Wybiera z listy wiadomo�ci, kt�re spe�niaj� wskazany warunek. Gdy nie ma wiadomo�ci
			 * spe�niaj�cych takie za�o�enia, czeka okre�lony czas do pojawienia si� PIERWSZEJ
			 * wiadomo�ci, kt�ra mo�e by� zwr�cona. Gdy czas oczekiwania zostanie przekroczony,
			 * zostanie zwr�cona pusta kolekcja wiadomo�ci.
			 *
			 * \param predicate Warunek, kt�ry musi zosta� spe�niony, by wiadomo�� by�a zwr�cona.
			 * \param timeout Maksymalny czas oczekiwania. Domy�lnie niesko�czono��.
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