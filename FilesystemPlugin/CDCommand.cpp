#include "CDCommand.h"
#include <Shlwapi.h>
#include <PluggableBot/External/format.h>
#include <algorithm>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		const std::string InvalidPath = "Ścieżka jest nieprawidłowa.";
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
			std::string path = context.ParseResults->GetParameter("to");
			std::replace(path.begin(), path.end(), '/', '\\');
			std::string newPath;
			if (!PathIsRelativeA(path.c_str()))
			{
				newPath = path;
			}
			else
			{
				auto currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
				char buffer[MAX_PATH];
				if (PathCombineA(buffer, currentDir.c_str(), path.c_str()) != nullptr)
				{
					PathAddBackslashA(buffer);
					newPath = buffer;
				}
			}
			if (newPath.empty() || !PathIsDirectoryA(newPath.c_str()))
			{
				return CommandExecutionResults(InvalidPath);
			}
			SetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender, newPath);
			return CommandExecutionResults(fmt::str(fmt::Format(PathChanged, newPath)));
		}

	}
}
