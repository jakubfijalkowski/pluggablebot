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
		 * \brief Zatrzymuje działanie aplikacji.
		 *
		 * Zatrzymanie aplikacji odbywa się przez wysłanie wiadomości
		 * Messages::ShutdownRequest.
		 *
		 * Składnia: `stop`
		 */
		class StopCommand
			: public ICommand
		{
		public:
			/**
			 * \brief Inicjalizuje komendę.
			 */
			StopCommand(ApplicationContext* context);

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
