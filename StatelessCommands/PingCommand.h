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
		 * Pinguje podany adres IP i zwraca, asynchronicznie, dane.
		 */
		class PingCommand
			: public ICommand
		{
		public:
			PingCommand(ApplicationContext* context);
			virtual const IMatcher* GetMatcher() const;
			virtual CommandExecutionResults Execute(const ExecutionContext& context);

		private:
			ApplicationContext* context;
			std::unique_ptr<RegexMatcher> matcher;
		};
	}
}
