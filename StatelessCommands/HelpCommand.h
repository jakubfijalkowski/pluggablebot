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
		 * \brief Wyświetla użytkownikowi pomoc.
		 *
		 * Pomoc zawiera listę dostępnych komend. Polecenie dodatkowo zwraca
		 * użytkownikowi obiekt JSON z polem *commands* zawierającym tablicę
		 * komend.
		 *
		 * Składnia: `help`
		 */
		class HelpCommand
			: public ICommand
		{
		public:
			/**
			 * \brief Inicjalizuje komendę.
			 */
			HelpCommand(ApplicationContext* context);

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
