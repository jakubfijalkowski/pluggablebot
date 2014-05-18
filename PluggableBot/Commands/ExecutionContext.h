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
		 * Kontekst wykonywania komendy - tworzony zaraz na pocz�tku procesu, w miar� przechodzenia kolejnych
		 * etap�w, uzupe�niany(np. ParseResult na pocz�tku jest puste).
		 */
		class PLUGIN_API ExecutionContext
		{
		public:
			/**
			 * Silnik u�ywany do wykonywania komend.
			 *
			 * Nie jest \a {smart pointer}em poniewa� jest to wska�nik na obiekt, kt�ry utworzy�
			 * kontekst i jest wa�ny tylko w trakcie wykonywania komendy. �adna z istniej�cych
			 * klas nie pasuje do wymog�w, dlatego u�ywany jest zwyk�y wska�nik.
			 */
			ICommandExecutor* const Executor;

			/**
			 * Wiadomo�� otrzymana od u�ytkownika.
			 */
			const UserMessagePointer Message;

			/**
			 * Wynik parsowania wiadomo�ci u�ytkownika. Dop�ki wiadomo�� nie zosta�a
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