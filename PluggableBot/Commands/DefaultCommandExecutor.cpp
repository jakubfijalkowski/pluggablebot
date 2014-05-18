#include <algorithm>
#include <functional>
#include "ICommandExecutor.h"

namespace PluggableBot
{
	namespace Commands
	{

		DefaultCommandExecutor::DefaultCommandExecutor(IParser* parser)
			: ICommandExecutor(parser), Logger(Logging::LogFactory::GetLogger("DefaultCommandExecutor"))
		{ }

		void DefaultCommandExecutor::AddCommands(const std::vector<CommandPointer>& from)
		{
			for (auto command : from)
			{
				if (command->GetMatcher()->IsFullText)
				{
					this->commands.push_back(command);
				}
				else
				{
					this->commands.insert(this->commands.begin(), command);
					this->normalCommandOffset++;
				}
			}
		}

		CommandExecutionResults DefaultCommandExecutor::Execute(UserMessagePointer message)
		{
			Logger->Debug("Starting executing the message:");
			Logger->Debug(message->Content);

			ExecutionContext context(this, message);

			context.ParseResults = this->Parser->Parse(message->Content);
			if (context.ParseResults->IsSuccess)
			{
				Logger->Information("Normal command received. Starting execution.");
			}
			else
			{
				Logger->Information("Cannot parse the command as a normal command. Assuming full-text.");
			}

			Logger->Debug("Trying to find an command.");
			auto command = find_if(
				this->commands.begin() + (context.ParseResults->IsSuccess ? 0 : this->normalCommandOffset),
				this->commands.end(), [&](CommandPointer cmd)
			{
				return cmd->GetMatcher()->Matches(context);
			});

			if (command == this->commands.end())
			{
				Logger->Warning("Cannot find command for message: {0}.", context.ParseResults->Name);
				throw Exceptions::NotFoundException("Cannot find command for the message.");
			}

			Logger->Information("Command {0} found. Executing.", (*command)->Name);
			return (*command)->Execute(context);
		}

	}
}