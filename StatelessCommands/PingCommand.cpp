#include <regex>
#include "PingCommand.h"

namespace PluggableBot
{
	namespace StatelessCommands
	{

		PingCommand::PingCommand(ApplicationContext* context)
			: ICommand("ping"), context(context), matcher(new RegexMatcher("ping (\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})"))
		{ }

		const IMatcher* PingCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults PingCommand::Execute(const ExecutionContext& context)
		{
			std::smatch match;
			std::regex_search(context.Message->Content, match, this->matcher->Expression);
			const std::string& ipAddress = match[1];

			return CommandExecutionResults(true);
		}

	}
}
