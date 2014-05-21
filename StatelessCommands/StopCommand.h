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
		 * Zatrzymuje działanie aplikacji.
		 */
		class StopCommand
			: public ICommand
		{
		public:
			StopCommand(ApplicationContext* context);
			virtual const IMatcher* GetMatcher() const;
			virtual CommandExecutionResults Execute(const ExecutionContext& context);

		private:
			ApplicationContext* context;
			std::unique_ptr<SimpleMatcher> matcher;
		};
	}
}
