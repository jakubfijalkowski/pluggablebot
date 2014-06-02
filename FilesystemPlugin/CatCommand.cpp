#include "CatCommand.h"
#include <Shlwapi.h>
#include <fstream>
#include <PluggableBot/Exceptions/ExecutionException.h>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		static const int64_t MaxFileLength = 1024 * 1024; // 1MB

		const std::string InvalidPath = "ścieżka jest nieprawidłowa.";
		const std::string PathIsNotFile = "nie można odczytać zawartości folderu";
		const std::string FileDoesNotExist = "podany plik nie istnieje";
		const std::string CannotReadFile = "nie udało się odczytać pliku";

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
				throw Exceptions::ExecutionException(InvalidPath);
			}
			if (PathIsDirectoryA(newPath.c_str()))
			{
				throw Exceptions::ExecutionException(PathIsNotFile);
			}
			if (!PathFileExistsA(newPath.c_str()))
			{
				throw Exceptions::ExecutionException(FileDoesNotExist);
			}

			std::ifstream file(newPath, std::ios_base::binary);
			file.seekg(0, std::ios_base::end);
			int64_t length = file.tellg();
			file.seekg(0, std::ios_base::beg);
			if (length == -1 || !file)
			{
				throw Exceptions::ExecutionException(CannotReadFile);
			}
			if (length > MaxFileLength)
			{
				length = MaxFileLength;
			}

			std::unique_ptr<char[]> buffer(new char[(unsigned)length + 1]);
			if (file.read(buffer.get(), length).bad())
			{
				throw Exceptions::ExecutionException(CannotReadFile);
			}
			buffer.get()[length] = 0;
			return CommandExecutionResults(std::string(buffer.get()));
		}

	}
}
