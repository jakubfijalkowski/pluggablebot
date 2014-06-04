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

		/**
		 * \brief Funkcja, która służy do filtrowania listy wiadomości.
		 */
		typedef std::function<bool(IMessage*)> MessagePredicate;

		/**
		 * \brief Lista wiadomości przefiltrowana przez Messenger.
		 */
		typedef std::list<MessagePointer> MessageList;
		
		/**
		 * \brief Wskaźnik na listę wiadomości.
		 */
		typedef std::shared_ptr<MessageList> MessageListPointer;

		/**
		 * \brief Posłaniec, czy też szyna wiadomości, który synchronizuje dostęp do głównego elementu
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
		 * Algorytm pobierania jednej wiadomości:
		 * 1. Wejdź do sekcji krytycznej. 
		 * 2. Sprawdź, czy istnieje wiadomość o określonym typie.
		 * 3. Jeśli tak, to:
		 *    - Usuń ją z kolekcji.
		 *    - Wyjdź z sekcji krytycznej.
		 *    - Zwróć ją i zakończ algorytm.
		 * 4. Jeśli nie, to wyjdź z sekcji krytycznej i przejdź dalej.
		 * 5. Zwiększ licznik oczekujących na wiadomość.
		 * 6. Czekaj na zdarzenie informujące o dodaniu wiadomości.
		 *    - Gdy zdarzenie nadejdzie, to rozpocznij algorytm od nowa.
		 *    - Gdy zdarzenie nie nadejdzie w określonym czasie, zwróć nullptr i zakończ algorytm.
		 *    - Zmniejsz licznik oczekujących na wiadomość niezależnie od w/w warunków.
		 *
		 * Algorytm pobierania wielu wiadomości:
		 * 1. Wejdź do sekcji krytycznej.
		 * 2. Wybierz z kolekcji te wiadomości, które spełniają dany predykat:
		 *    - Sprawdź, czy wiadomość spełnia warunek. Jeśli tak to przejdź dalej, jeśli nie to
		 *      przejdź do kolejnej wiadomości.
		 *    - Dodaj wiadomość do kolekcji wybranych wiadomości.
		 *    - Usuń wiadomość z kolekcji.
		 *    - Przejdź do następnej wiadomości lub wyjdź z pętli.
		 * 3. Wyjdź z sekcji krytycznej.
		 * 4. Jeśli kolekcja zapisanych wiadomości nie jest pusta, zwróć ją i zakończ algorytm.
		 * 5. Jeśli kolekcja zapisanych wiadomości jest pusta, to przejdź dalej.
		 * 6. Zwiększ licznik oczekujących na wiadomość.
		 * 7. Czekaj na zdarzenie informujące o dodaniu wiadomości.
		 *    - Gdy zdarzenie nadejdzie, to rozpocznij algorytm od nowa.
		 *    - Gdy zdarzenie nie nadejdzie w określonym czasie, zwróć pustą kolekcję i zakończ
		 *      algorytm.
		 *    - Zmniejsz licznik oczekujących na wiadomość niezależnie od w/w warunków.
		 *
		 * Algorytm dodawania nowej wiadomości:
		 * 1. Wejdź do sekcji krytycznej.
		 * 2. Dodaj wiadomośc do kolekcji.
		 * 3. Wyjdź z sekcji krytycznej.
		 * 4. Jeśli licznik oczekujących na wiadomość nie jest zerem, to wyślij zdarzenie otrzymania
		 *    nowej wiadomości.
		 *
		 * \sa
		 * \ref PluggableBot::Messages
		 */
		class PLUGIN_API Messenger
		{
		public:
			/**
			 * \brief Inicjalizuje nowy obiekt.
			 */
			Messenger();

			/**
			 * \brief Czyści obiekt, usuwając pozostałe wiadomości.
			 */
			~Messenger();

			/**
			 * \brief Wysyła wskazaną wiadomość do wszystkich.
			 */
			void Send(MessagePointer message);

			/**
			 * \brief Badziej przejrzysta wersja `Get(type, 0)`.
			 */
			MessagePointer TryGet(int type)
			{
				return this->Get(type, 0);
			}

			/**
			 * \brief Badziej przejrzysta wersja `Get(predicate, 0)`.
			 */
			MessageListPointer TryGet(MessagePredicate predicate)
			{
				return this->Get(predicate, 0);
			}

			/**
			 * \brief Pobiera jedną wiadomość z list o wskazanym typie.
			 * Jeśli takowa nie istnieje - czeka określony czas aż się pojawi i ją zwraca.
			 * Jeśli czas oczekiwania zostanie przekroczony, zostaje zwrócony `nullptr`.
			 *
			 * \param type Typ wiadomości, której oczekujemy.
			 * \param timeout Maksymalny czas oczekiwania. Domyślnie nieskończoność.
			 * \returns Wskaźnik na wiadomość *lub* `nullptr`, gdy wiadomość nie istnieje
			 */
			MessagePointer Get(int type, DWORD timeout = INFINITE);

			/**
			 * \brief Wybiera z listy wiadomości, które spełniają wskazany warunek.
			 * Gdy nie ma * wiadomości spełniających kryteria, czeka określony czas do pojawienia
			 * się PIERWSZEJ wiadomości, która może być zwrócona. Gdy czas oczekiwania zostanie
			 * przekroczony, zostanie zwrócona pusta kolekcja wiadomości.
			 *
			 * \param predicate Warunek, który musi zostać spełniony, by wiadomość była zwrócona.
			 * \param timeout Maksymalny czas oczekiwania. Domyślnie nieskończoność.
			 * \returns Lista wiadomości *lub* pusta lista, gdy nie pojawiły się widomości
			 *          spełniające wskazany warunek.
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