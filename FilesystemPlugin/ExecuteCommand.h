#pragma once
#include <memory>
#include <PluggableBot/ApplicationContext.h>
#include <PluggableBot/Commands/ICommand.h>

namespace PluggableBot
{
	namespace FilesystemPlugin
	{
		using namespace PluggableBot::Commands;

		/**
		 * \brief Wywołuje, asynchronicznie, podane polecenie i odsyła wynik.
		 *
		 * Składnia: `execute command="polecenie"`
		 */
		class ExecuteCommand
			: public ICommand
		{
		public:
			/**
			 * \brief Inicjalizuje komendę.
			 */
			ExecuteCommand(ApplicationContext* context);

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
