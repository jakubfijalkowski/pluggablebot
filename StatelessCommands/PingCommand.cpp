#include <future>
#include <PluggableBot/Messages/Messages.h>
#include <PluggableBot/Other.h>
#include "PingCommand.h"

#undef SendMessage

namespace PluggableBot
{
	namespace StatelessCommands
	{

		static const std::string CannotPingMessage = "nie udało się wywołać polecenia PING";

		PingCommand::PingCommand(ApplicationContext* context)
			: ICommand("ping"), context(context), matcher(new SimpleMatcher("ping", { "address" }))
		{ }

		const IMatcher* PingCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults PingCommand::Execute(const ExecutionContext& context)
		{
			const std::string commandLine = "ping " + context.ParseResults->GetParameter("address");
			const auto userMsg = context.Message;
			std::async(std::launch::async, [=]()
			{
				try
				{
					auto response = Other::CallSystemCommand(commandLine, "");
					auto message = new Messages::SendMessage(response, userMsg->Sender, userMsg->SourceProtocol);
					this->context->Messenger->Send(Messaging::MessagePointer(message));
				}
				catch (std::system_error ex)
				{
					auto message = new Messages::AsyncExecutionFailure(this,
						CannotPingMessage, ex.code().value(),
						userMsg->Sender, userMsg->SourceProtocol);
					this->context->Messenger->Send(Messaging::MessagePointer(message));
				}
			});

			return CommandExecutionResults(true);
		}

	}
}
