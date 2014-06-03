#include "LsCommand.h"
#include <Windows.h>
#include <PluggableBot/Other.h>
#include <PluggableBot/Exceptions/ExecutionException.h>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		static const std::string Header = "Lista plików w aktualnym katalogu:";
		static const std::string CannotListFile = "nie udało się wylistować plików";
		static const std::string CannotListAllFiles = "Nie udało się wylistować wszystkich plików. Powyższa lista może nie być pełna.";

		LsCommand::LsCommand(ApplicationContext* context)
			: ICommand("ls"), context(context), matcher(new SimpleMatcher("ls", {}))
		{ }

		const IMatcher* LsCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults LsCommand::Execute(const ExecutionContext& context)
		{
			auto searchQuery = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			searchQuery += "*.*";

			std::string result = Header;

			auto queryConverted = Other::UTF8ToWideString(searchQuery);
			WIN32_FIND_DATAW ffd;
			HANDLE hFind = FindFirstFileW(queryConverted.get(), &ffd);

			if (hFind == INVALID_HANDLE_VALUE)
			{
				throw Exceptions::ExecutionException(CannotListFile);
			}

			do
			{
				if (wcscmp(ffd.cFileName, L".") != 0 && wcscmp(ffd.cFileName, L"..") != 0)
				{
					result += "\n";
					result += Other::WideCharToUTF8(ffd.cFileName);
				}
			} while (FindNextFileW(hFind, &ffd));

			DWORD lastError = GetLastError();
			if (lastError != ERROR_NO_MORE_FILES)
			{
				result += "\n";
				result += CannotListAllFiles;
			}
			else
			{
				FindClose(hFind);
			}

			return CommandExecutionResults(result);
		}

	}
}
