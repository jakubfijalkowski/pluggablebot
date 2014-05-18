#include <PluggableBot/Messages/Messages.h>
#include "StopCommand.h"

namespace PluggableBot
{
	namespace StatelessCommands
	{

		StopCommand::StopCommand(ApplicationContext* context)
			: ICommand("stop"), context(context), matcher(new SimpleMatcher("stop", {}))
		{ }

		const IMatcher* StopCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults StopCommand::Execute(const ExecutionContext& context)
		{
			this->context->Messenger->Send(Messaging::MessagePointer(new Messages::ShutdownRequest()));
			return CommandExecutionResults("Aplikacja zostanie wy³¹czona.");
		}

	}
}
