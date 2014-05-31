#include "PWDCommand.h"
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		PWDCommand::PWDCommand(ApplicationContext* context)
			: ICommand("pwd"), context(context), matcher(new SimpleMatcher("pwd", {}))
		{ }

		const IMatcher* PWDCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults PWDCommand::Execute(const ExecutionContext& context)
		{
			return CommandExecutionResults(GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender));
		}

	}
}
