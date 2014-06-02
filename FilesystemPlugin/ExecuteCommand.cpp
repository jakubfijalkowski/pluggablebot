#include "ExecuteCommand.h"
#include <PluggableBot/Other.h>
#include <PluggableBot/Messages/Messages.h>
#include <future>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		const std::string CannotExecuteCommand = "nie udało się wywołać polecenia";

		ExecuteCommand::ExecuteCommand(ApplicationContext* context)
			: ICommand("execute"), context(context), matcher(new SimpleMatcher("execute", { "command" }))
		{ }

		const IMatcher* ExecuteCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults ExecuteCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			auto& command = context.ParseResults->GetParameter("command");
			const auto userMsg = context.Message;

			std::async(std::launch::async, [=]()
			{
				try
				{
					auto content = Other::CallSystemCommand(command, currentDir);
					auto message = new Messages::SendMessage(content, userMsg->Sender, userMsg->SourceProtocol);
					this->context->Messenger->Send(Messaging::MessagePointer(message));
				}
				catch (std::system_error ex)
				{
					auto message = new Messages::AsyncExecutionFailure(this,
						CannotExecuteCommand, ex.code().value(),
						userMsg->Sender, userMsg->SourceProtocol);
					this->context->Messenger->Send(Messaging::MessagePointer(message));
				}
			});
			return CommandExecutionResults(true);
		}

	}
}
