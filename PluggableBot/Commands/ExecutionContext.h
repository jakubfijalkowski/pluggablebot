#pragma once
#include <memory>
#include "../Config.h"
#include "ParseResults.h"
#include "../UserMessage.h"

namespace PluggableBot
{
	class IProtocol;

	namespace Commands
	{
		class ICommandExecutor;

		/**
		 * \brief Kontekst wykonywania komendy - tworzony zaraz na początku procesu, w miarę przechodzenia kolejnych
		 * etapów, uzupełniany(np. ParseResult na początku jest puste).
		 *
		 * Używany do nadzorowania procesu i przekazywania informacji pomiędzy poszczególnymi etapami.
		 */
		class PLUGIN_API ExecutionContext
		{
		public:
			/**
			 * \brief Silnik używany do wykonywania komend.
			 *
			 * Nie jest `smart pointer`em ponieważ jest to wskaźnik na obiekt, który utworzył
			 * kontekst i jest ważny tylko w trakcie wykonywania komendy. Żadna z istniejących
			 * klas nie pasuje do wymogów, dlatego używany jest zwykły wskaźnik.
			 */
			ICommandExecutor* const Executor;

			/**
			 * \brief Wiadomość otrzymana od użytkownika.
			 */
			const UserMessagePointer Message;

			/**
			 * \brief Wynik parsowania wiadomości użytkownika. Dopóki wiadomość nie została
			 * sparsowana, jest nullem.
			 */
			ParseResultsPointer ParseResults;

			/**
			 * \brief Inicjalizuje obiekt.
			 */
			ExecutionContext(ICommandExecutor* executor, UserMessagePointer userMessage)
				: Executor(executor), Message(userMessage)
			{ }
		};
		
	}
}