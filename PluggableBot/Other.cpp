#include "Other.h"

namespace PluggableBot
{
	namespace Other
	{

		std::string ReadFromPipe(HANDLE hPipe)
		{
			static const int BufferSize = 4096;

			std::string content;

			DWORD read;
			CHAR buffer[BufferSize + 1];
			BOOL success;
			do
			{
				success = ReadFile(hPipe, buffer, BufferSize, &read, nullptr);

				buffer[read] = 0;
				content += buffer;

			} while (success && read == BufferSize);
			return content;
		}


		std::string CallSystemCommand(const std::string& command, const std::string& workingDirectory)
		{
			SECURITY_ATTRIBUTES saAttr;
			saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
			saAttr.bInheritHandle = TRUE;
			saAttr.lpSecurityDescriptor = NULL;
			HANDLE hChildOutRead = nullptr, hChildOutWrite = nullptr;
			if (!CreatePipe(&hChildOutRead, &hChildOutWrite, &saAttr, 0))
			{
				throw std::system_error(std::error_code(GetLastError(), std::system_category()), "Cannot create pipe.");
			}

			PROCESS_INFORMATION procInfo;
			STARTUPINFOA startInfo;

			ZeroMemory(&procInfo, sizeof(PROCESS_INFORMATION));
			ZeroMemory(&startInfo, sizeof(STARTUPINFO));

			startInfo.cb = sizeof(STARTUPINFO);
			startInfo.hStdOutput = hChildOutWrite;
			startInfo.hStdError = hChildOutWrite;
			startInfo.dwFlags |= STARTF_USESTDHANDLES;

			auto success = CreateProcessA(nullptr, (char*)command.c_str(), nullptr, nullptr, TRUE, 0, nullptr,
				workingDirectory.empty() ? nullptr : workingDirectory.c_str(),
				&startInfo, &procInfo);
			if (!success)
			{
				CloseHandle(hChildOutRead);
				CloseHandle(hChildOutWrite);
				throw std::system_error(std::error_code(GetLastError(), std::system_category()), "Cannot start process.");
			}

			WaitForSingleObject(procInfo.hProcess, INFINITE);
			CloseHandle(procInfo.hProcess);
			CloseHandle(procInfo.hThread);

			std::string message = ReadFromPipe(hChildOutRead);

			CloseHandle(hChildOutRead);
			CloseHandle(hChildOutWrite);
			return message;
		}

		std::string FormatError(DWORD code)
		{
			WCHAR* wideMessage;
			FormatMessageW(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr,
				code,
				MAKELANGID(LANG_POLISH, SUBLANG_POLISH_POLAND),
				(LPWSTR)&wideMessage,
				0, nullptr);

			std::string converted = WideCharToUTF8(wideMessage);
			LocalFree(wideMessage);
			return converted;
		}

		std::string WideCharToUTF8(const wchar_t* str)
		{
			int length = WideCharToMultiByte(CP_UTF8, 0, str, -1, nullptr, 0, nullptr, nullptr);
			char* message = new char[length + 1];
			message[length] = 0;
			WideCharToMultiByte(CP_UTF8, 0, str, -1, message, length, nullptr, nullptr);
			std::string converted = message;
			delete[] message;
			return converted;
		}

		std::shared_ptr<wchar_t> UTF8ToWideString(const std::string& str)
		{
			wchar_t* message = new wchar_t[str.length() + 1];
			int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), message, str.length());
			message[len] = 0;
			return std::shared_ptr<wchar_t>(message, std::default_delete<wchar_t[]>());
		}
	}
}