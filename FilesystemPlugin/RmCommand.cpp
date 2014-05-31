#include "RmCommand.h"
#include <Shlwapi.h>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		const std::string FileDoesNotExist = "Podany plik nie istnieje!";
		const std::string CannotDeleteFile = "Nie udało się usunąć pliku.";
		const std::string FileDeleted = "Usunięto.";

		RmCommand::RmCommand(ApplicationContext* context)
			: ICommand("rm"), context(context), matcher(new SimpleMatcher("rm", { "file" }))
		{ }

		const IMatcher* RmCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults RmCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			std::string filePath = JoinPath(currentDir, SanitizePath(context.ParseResults->GetParameter("file")));

			if (!PathFileExistsA(filePath.c_str()))
			{
				return CommandExecutionResults(FileDoesNotExist);
			}
			if (!DeleteFileA(filePath.c_str()))
			{
				return CommandExecutionResults(CannotDeleteFile);
			}
			return CommandExecutionResults(FileDeleted);
		}

	}
}
