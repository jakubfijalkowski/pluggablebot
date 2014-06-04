#include "ListProtocolsCommand.h"

namespace PluggableBot
{
	namespace StatelessCommands
	{

		ListProtocolsCommand::ListProtocolsCommand(ApplicationContext* context)
			: ICommand("listprotocols"), context(context), matcher(new SimpleMatcher("listprotocols", {}))
		{ }

		const IMatcher* ListProtocolsCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults ListProtocolsCommand::Execute(const ExecutionContext& context)
		{
			std::string message = "Lista protokołów:\n";
			jsonxx::Array protocolsArray;
			for (auto& protocol : *this->context->Protocols)
			{
				jsonxx::Object protocolState;
				protocolState << "name" << protocol.Protocol->Name;
				protocolState << "isWorking" << protocol.IsWorking;
				protocolsArray << protocolState;

				message += protocol.Protocol->Name;
				message += " - ";
				message += protocol.IsWorking ? "działa" : "nie działa";
				message += "\n";
			}
			std::shared_ptr<jsonxx::Object> o(new jsonxx::Object());
			(*o) << "protocols" << protocolsArray;
			return CommandExecutionResults(message, false, std::move(o));
		}

	}
}
