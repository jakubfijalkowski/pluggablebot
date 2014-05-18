#include "HelpCommand.h"

namespace PluggableBot
{
	namespace StatelessCommands
	{

		HelpCommand::HelpCommand(ApplicationContext* context)
			: ICommand("help"), context(context), matcher(new SimpleMatcher("help", {}))
		{ }

		const IMatcher* HelpCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults HelpCommand::Execute(const ExecutionContext& context)
		{
			std::string message = "Lista komend:\n";
			jsonxx::Array commandsArray;
			for (auto cmd : context.Executor->GetCommands())
			{
				commandsArray << cmd->Name;

				message += cmd->Name;
				message += "\n";
			}
			std::shared_ptr<jsonxx::Object> o(new jsonxx::Object());
			(*o) << "commands" << commandsArray;
			return CommandExecutionResults(message, false, std::move(o));
		}

	}
}
