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
		 * Kontekst wykonywania komendy - tworzony zaraz na pocz¹tku procesu, w miarê przechodzenia kolejnych
		 * etapów, uzupe³niany(np. ParseResult na pocz¹tku jest puste).
		 */
		class PLUGIN_API ExecutionContext
		{
		public:
			/**
			 * Silnik u¿ywany do wykonywania komend.
			 *
			 * Nie jest \a {smart pointer}em poniewa¿ jest to wskaŸnik na obiekt, który utworzy³
			 * kontekst i jest wa¿ny tylko w trakcie wykonywania komendy. ¯adna z istniej¹cych
			 * klas nie pasuje do wymogów, dlatego u¿ywany jest zwyk³y wskaŸnik.
			 */
			ICommandExecutor* const Executor;

			/**
			 * Wiadomoœæ otrzymana od u¿ytkownika.
			 */
			const UserMessagePointer Message;

			/**
			 * Wynik parsowania wiadomoœci u¿ytkownika. Dopóki wiadomoœæ nie zosta³a
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