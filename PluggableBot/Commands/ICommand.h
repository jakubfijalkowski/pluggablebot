#pragma once
#include <memory>
#include "../Config.h"
#include "IMatcher.h"
#include "CommandExecutionResults.h"
#include "ExecutionContext.h"
#include "../Exceptions/ExecutionException.h"

namespace PluggableBot
{
	/**
	 * \brief Przestrzeń nazw zawierająca wszystkie klasy i interfejsy związane z komendami.
	 */
	namespace Commands
	{

		/**
		 * \brief Interfejs komend. Dostarcza podstawowych informacji o komendzie oraz obsługuje jej wywołanie.
		 *
		 * ### Założenia ###
		 * Każda z komend powinna wykonywać jedną, ściśle określoną akcję. Nie ma ograniczeń, co do
		 * przechowywania stanu, lecz po stronie wtyczki i komendy jest odpowiedzialność za przechowywanie tego
		 * stanu(aczkolwiek aplikacja udostępnia mechanizmy upraszczające takie działania). Polecenia nie powinny
		 * zmieniać stanu globalnego aplikacji lub ingerować w niepowiązane komendy. Mogą one współpracować ze
		 * sobą, o ile każda z nich zostało do tego zaprojektowana.
		 * 
		 * Komendy przeważnie nie powinny komunikować się z klientem w sposób bezpośredni. Jeśli jednak akcja wymaga
		 * dłuższego czasu na wykonanie, nie powinna być uruchamiana w głównym wątku aplikacji. Komenda powinna utworzyć
		 * nowy wątek i zwrócić status oznajmiając użytkownikowi, że akcja jest w trakcie wykonywania. Po zakończeniu
		 * akcji powinna poinformować użytkownika o jej zakończeniu, używając mechanizmów udostępnionych przez aplikację.
		 *
		 * ### Działanie ###
		 * Komenda, która została znaleziona w trakcje interpretacji wiadomości, zostaje wywołana w głównym
		 * wątku aplikacji. Do metody akcji zostają przekazane wszystkie niezbędne informacje, włącznie z
		 * przesłaną wiadomością(całą) oraz wynikiem jej parsowania, informacjami o użytkowników oraz
		 * źródle wiadomości(wtyczce). 
		 *
		 * Gdy w trakcie wykonywania akcji nastąpi błąd, wtyczka powinna rzucić odpowiedni wyjątek. Gdy funkcja zwróci
		 * wartość, oznacza to pomyślne wykonanie akcji. Wartość zwracana przez wtyczkę to wiadomość tekstowa, która może
		 * zostać bezproblemowo przekazana użytkownikowi, oraz opcjonalne dane, które mogą zostać wykorzystane przez
		 * maszynowych użytkowników.
		 *
		 * \sa
		 * \ref UserMessage
		 * \ref Messages::AsyncCommandExecuted
		 * \ref CommandExecutionResults
		 * \ref Messages::AsyncExecutionFailure
		 * \ref Exceptions::ExecutionException
		 */
		class PLUGIN_API ICommand
		{
		public:
			/**
			 * \brief Nazwa komendy. Używana tylko ze względów informacyjnych.
			 */
			const std::string Name;

			/**
			 * \brief Pobiera IMatcher, który jest odpowiedzialny za dopasowanie wiadomości do komendy.
			 */
			virtual const IMatcher* GetMatcher() const = 0;

			/**
			 * \brief Wykonuje metodę i zwraca odpowiedź która zostanie dostarczona użytkownikowi.
			 *
			 * By zgłosić błąd, metoda powinna rzucić wyjątek dziedziczący z ExecutionException lub
			 * jego samego.
			 *
			 * \exception ExecutionException Rzucany, gdy nie powiodło się wykonanie metody.
			 * \param context Kontekst wywołania komendy(w pełni uzupełniony).
			 */
			virtual CommandExecutionResults Execute(const ExecutionContext& context) = 0;

			virtual ~ICommand() { }

		protected:
			/**
			 * \brief Inicjalizuje komendę.
			 */
			ICommand(const std::string& name)
				: Name(name)
			{ }
		};

		/**
		 * \brief Wskaźnik na komendę używaną przez aplikację.
		 *
		 * Nie jest `smart pointer`em, gdyż komenda jest zarządzana przez Plugins::IPlugin
		 * i to ta klasa jest odpowiedzialna za prawidłowe zarządzanie okresem życia
		 * obiektu.
		 */
		typedef ICommand* CommandPointer;

	}
}