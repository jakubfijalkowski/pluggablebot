#include "CatCommand.h"
#include <Shlwapi.h>
#include <algorithm>
#include <fstream>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		static const int64_t MaxFileLength = 1024 * 1024; // 1MB

		const std::string InvalidPath = "Ścieżka jest nieprawidłowa.";
		const std::string PathIsNotFile = "Nie można odczytać zawartości folderu!";
		const std::string FileDoesNotExist = "Podany plik nie istnieje!";
		const std::string CannotReadFile = "Nie udało się odczytać pliku.";

		CatCommand::CatCommand(ApplicationContext* context)
			: ICommand("cat"), context(context), matcher(new SimpleMatcher("cat", { "file" }))
		{ }

		const IMatcher* CatCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults CatCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			std::string path = SanitizePath(context.ParseResults->GetParameter("file"));
			std::string newPath = JoinPath(currentDir, path);
			if (newPath.empty())
			{
				return CommandExecutionResults(InvalidPath);
			}
			if (PathIsDirectoryA(newPath.c_str()))
			{
				return CommandExecutionResults(PathIsNotFile);
			}
			if (!PathFileExistsA(newPath.c_str()))
			{
				return CommandExecutionResults(FileDoesNotExist);
			}

			std::ifstream file(newPath, std::ios_base::binary);
			file.seekg(0, std::ios_base::end);
			int64_t length = file.tellg();
			file.seekg(0, std::ios_base::beg);
			if (length == -1 || !file)
			{
				return CommandExecutionResults(CannotReadFile);
			}
			if (length > MaxFileLength)
			{
				length = MaxFileLength;
			}

			std::unique_ptr<char[]> buffer(new char[(unsigned)length + 1]);
			if (file.read(buffer.get(), length).bad())
			{
				return CommandExecutionResults(CannotReadFile);
			}
			buffer.get()[length] = 0;
			return CommandExecutionResults(std::string(buffer.get()));
		}

	}
}
