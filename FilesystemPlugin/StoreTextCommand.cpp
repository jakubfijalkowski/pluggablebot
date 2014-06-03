#include "StoreTextCommand.h"
#include <Shlwapi.h>
#include <fstream>
#include <PluggableBot/Exceptions/ExecutionException.h>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		const std::string InvalidPath = "ścieżka jest nieprawidłowa";
		const std::string PathIsNotFile = "nie można nadpisać zawartości folderu";
		const std::string CannotWriteToFile = "nie udało się zapisać pliku";
		const std::string FileWritten = "Plik został zapisany.";

		StoreTextCommand::StoreTextCommand(ApplicationContext* context)
			: ICommand("storetext"), context(context), matcher(new SimpleMatcher("storetext", { "file", "content" }))
		{ }

		const IMatcher* StoreTextCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults StoreTextCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			auto& content = context.ParseResults->GetParameter("content");
			auto path = SanitizePath(context.ParseResults->GetParameter("file"));
			auto newPath = JoinPath(currentDir, path);
			if (newPath.empty())
			{
				throw Exceptions::ExecutionException(InvalidPath);
			}
			if (PathIsDirectoryA(newPath.c_str()))
			{
				throw Exceptions::ExecutionException(PathIsNotFile);
			}

			std::ofstream file(newPath, std::ios_base::binary | std::ios_base::trunc);
			file.write(content.c_str(), content.size());
			if (!file)
			{
				throw Exceptions::ExecutionException(CannotWriteToFile);
			}
			return CommandExecutionResults(FileWritten);
		}

	}
}
