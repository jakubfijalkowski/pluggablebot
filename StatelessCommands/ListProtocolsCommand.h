#pragma once
#include <memory>
#include <PluggableBot/ApplicationContext.h>
#include <PluggableBot/Commands/ICommand.h>

namespace PluggableBot
{
	namespace StatelessCommands
	{
		using namespace PluggableBot::Commands;
		
		/**
		 * \brief Wyświetla listę protokołów wraz ze stanem.
		 *
		 * Pomoc zawiera listę dostępnych komend. Polecenie dodatkowo zwraca
		 * użytkownikowi obiekt JSON z polem *commands* zawierającym tablicę
		 * obiektów o następujących właściwościach:
		 * - *name* - nazwa protokołu.
		 * - *isWorking* - *true* / *false* - określa, czy protokół działa.
		 *
		 * Składnia: `listprotocols`
		 */
		class ListProtocolsCommand
			: public ICommand
		{
		public:
			/**
			 * \brief Inicjalizuje komendę.
			 */
			ListProtocolsCommand(ApplicationContext* context);

			/**
			 * \brief Zwraca SimpleMatcher odpowiedzialny za dopasowanie komendy.
			 */
			virtual const IMatcher* GetMatcher() const;

			/**
			 * \brief Wywołuje komendę.
			 */
			virtual CommandExecutionResults Execute(const ExecutionContext& context);

		private:
			ApplicationContext* context;
			std::unique_ptr<SimpleMatcher> matcher;
		};
	}
}
