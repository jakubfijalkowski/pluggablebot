#include <future>
#include <PluggableBot/Messages/Messages.h>
#include <PluggableBot/Other.h>
#include "PingCommand.h"

#undef SendMessage

namespace PluggableBot
{
	namespace StatelessCommands
	{

		static const std::string CannotPingMessage = "Nie udało się wywołać polecenia PING.";

		std::string SystemPing(const std::string& address)
		{
			const std::string CommandLine = "ping " + address;

			try
			{
				return Other::CallSystemCommand(CommandLine, "");
			}
			catch (...)
			{
				return CannotPingMessage;
			}
		}


		PingCommand::PingCommand(ApplicationContext* context)
			: ICommand("ping"), context(context), matcher(new SimpleMatcher("ping", { "address" }))
		{ }

		const IMatcher* PingCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults PingCommand::Execute(const ExecutionContext& context)
		{
			auto address = context.ParseResults->GetParameter("address");
			const auto userMsg = context.Message;
			std::async(std::launch::async, [=]()
			{
				auto response = SystemPing(address);
				auto message = new Messages::SendMessage(response, userMsg->Sender, userMsg->SourceProtocol);
				this->context->Messenger->Send(Messaging::MessagePointer(message));
			});

			return CommandExecutionResults(true);
		}

	}
}
