#include "SendCommand.h"
#include <string>
#include <algorithm>
#include <PluggableBot/Messages/Messages.h>
#include <PluggableBot/Exceptions/ExecutionException.h>

namespace PluggableBot
{
	namespace StatelessCommands
	{

		const std::string NoProtocol = "podany protokół nie istnieje";
		const std::string ProtocolIsNotWorking = "podany protokół nie działa prawidłowo";
		const std::string MessageSent = "Wiadomość została wysłana.";

		SendCommand::SendCommand(ApplicationContext* context)
			: ICommand("send"), context(context), matcher(new SimpleMatcher("send", { "to", "by", "msg" }))
		{ }

		const IMatcher* SendCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults SendCommand::Execute(const ExecutionContext& context)
		{
			auto protocolName = context.ParseResults->GetParameter("by");
			auto protocol = std::find_if(this->context->Protocols->begin(), this->context->Protocols->end(), [&](const ProtocolState& state)
			{
				return state.Protocol->Name.compare(0, protocolName.length(), protocolName.c_str()) == 0;
			});

			if (protocol == this->context->Protocols->end())
			{
				throw Exceptions::ExecutionException(NoProtocol);
			}
			else if (!protocol->IsWorking)
			{
				throw Exceptions::ExecutionException(ProtocolIsNotWorking);
			}

			auto msg = new Messages::SendMessage(context.ParseResults->GetParameter("msg"), context.ParseResults->GetParameter("to"), protocol->Protocol);
			this->context->Messenger->Send(Messaging::MessagePointer(msg));

			return CommandExecutionResults(MessageSent);
		}

	}
}
