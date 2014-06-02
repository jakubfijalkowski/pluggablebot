#include "CDCommand.h"
#include <Shlwapi.h>
#include <PluggableBot/External/format.h>
#include <PluggableBot/Exceptions/ExecutionException.h>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		const std::string InvalidPath = "ścieżka jest nieprawidłowa";
		const std::string PathChanged = "Ścieżka została zmieniona na '{0}'.";

		CDCommand::CDCommand(ApplicationContext* context)
			: ICommand("cd"), context(context), matcher(new SimpleMatcher("cd", { "to" }))
		{ }

		const IMatcher* CDCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults CDCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			std::string path = SanitizePath(context.ParseResults->GetParameter("to"));
			std::string newPath = JoinPath(currentDir, path);

			if (newPath.empty() || !PathIsDirectoryA(newPath.c_str()))
			{
				throw Exceptions::ExecutionException(InvalidPath);
			}
			SetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender, newPath);
			return CommandExecutionResults(fmt::str(fmt::Format(PathChanged, newPath)));
		}

	}
}
