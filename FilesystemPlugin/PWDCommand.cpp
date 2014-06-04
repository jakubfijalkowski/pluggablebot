#include "PwdCommand.h"
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		PwdCommand::PwdCommand(ApplicationContext* context)
			: ICommand("pwd"), context(context), matcher(new SimpleMatcher("pwd", {}))
		{ }

		const IMatcher* PwdCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults PwdCommand::Execute(const ExecutionContext& context)
		{
			return CommandExecutionResults(GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender));
		}

	}
}
