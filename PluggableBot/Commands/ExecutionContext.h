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
		 * Kontekst wykonywania komendy - tworzony zaraz na początku procesu, w miarę przechodzenia kolejnych
		 * etapów, uzupełniany(np. ParseResult na początku jest puste).
		 */
		class PLUGIN_API ExecutionContext
		{
		public:
			/**
			 * Silnik używany do wykonywania komend.
			 *
			 * Nie jest \a {smart pointer}em ponieważ jest to wskaźnik na obiekt, który utworzył
			 * kontekst i jest ważny tylko w trakcie wykonywania komendy. Żadna z istniejących
			 * klas nie pasuje do wymogów, dlatego używany jest zwykły wskaźnik.
			 */
			ICommandExecutor* const Executor;

			/**
			 * Wiadomość otrzymana od użytkownika.
			 */
			const UserMessagePointer Message;

			/**
			 * Wynik parsowania wiadomości użytkownika. Dopóki wiadomość nie została
			 * sparsowana, jest nullem.
			 */
			ParseResultsPointer ParseResults;

			/**
			 * Inicjalizuje obiekt.
			 */
			ExecutionContext(ICommandExecutor* executor, UserMessagePointer userMessage)
				: Executor(executor), Message(userMessage)
			{ }
		};
		
	}
}