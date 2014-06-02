#include "MvCommand.h"
#include <Shlwapi.h>
#include <PluggableBot/Exceptions/ExecutionException.h>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		const std::string FileDoesNotExist = "podany plik nie istnieje";
		const std::string CannotMoveFile = "nie udało się przenieść pliku/katalogu";
		const std::string FileMoved = "Przeniesiono.";

		MvCommand::MvCommand(ApplicationContext* context)
			: ICommand("mv"), context(context), matcher(new SimpleMatcher("mv", { "from", "to" }))
		{ }

		const IMatcher* MvCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults MvCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			std::string fromPath = JoinPath(currentDir, SanitizePath(context.ParseResults->GetParameter("from")));
			std::string toPath = JoinPath(currentDir, (context.ParseResults->GetParameter("to")));

			if (!PathFileExistsA(fromPath.c_str()))
			{
				throw Exceptions::ExecutionException(FileDoesNotExist);
			}
			if (!MoveFileA(fromPath.c_str(), toPath.c_str()))
			{
				throw Exceptions::ExecutionException(CannotMoveFile);
			}
			return CommandExecutionResults(FileMoved);
		}

	}
}
