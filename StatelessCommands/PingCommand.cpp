#include <regex>
#include <future>
#include <PluggableBot/Messages/Messages.h>
#include "PingCommand.h"

#undef SendMessage

namespace PluggableBot
{
	namespace StatelessCommands
	{

		static const std::string CannotPingMessage = "Nie udało się wywołać polecenia PING.";

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

		std::string SystemPing(const std::string& address)
		{
			const std::string CommandLine = "ping " + address;

			SECURITY_ATTRIBUTES saAttr;
			saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
			saAttr.bInheritHandle = TRUE;
			saAttr.lpSecurityDescriptor = NULL;
			HANDLE hChildOutRead = nullptr, hChildOutWrite = nullptr;
			if (!CreatePipe(&hChildOutRead, &hChildOutWrite, &saAttr, 0))
			{
				return CannotPingMessage;
			}

			PROCESS_INFORMATION procInfo;
			STARTUPINFOA startInfo;

			ZeroMemory(&procInfo, sizeof(PROCESS_INFORMATION));
			ZeroMemory(&startInfo, sizeof(STARTUPINFO));

			startInfo.cb = sizeof(STARTUPINFO);
			startInfo.hStdOutput = hChildOutWrite;
			startInfo.hStdError = hChildOutWrite;
			startInfo.dwFlags |= STARTF_USESTDHANDLES;

			auto success = CreateProcessA(nullptr, (char*)CommandLine.c_str(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &startInfo, &procInfo);
			if (!success)
			{
				CloseHandle(hChildOutRead);
				CloseHandle(hChildOutWrite);
				return CannotPingMessage;
			}

			WaitForSingleObject(procInfo.hProcess, INFINITE);
			CloseHandle(procInfo.hProcess);
			CloseHandle(procInfo.hThread);

			std::string message = ReadFromPipe(hChildOutRead);

			CloseHandle(hChildOutRead);
			CloseHandle(hChildOutWrite);
			return message;
		}


		PingCommand::PingCommand(ApplicationContext* context)
			: ICommand("ping"), context(context), matcher(new RegexMatcher("ping (.+)"))
		{ }

		const IMatcher* PingCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults PingCommand::Execute(const ExecutionContext& context)
		{
			std::smatch match;
			std::regex_search(context.Message->Content, match, this->matcher->Expression);

			const std::string& address = match[1];
			const auto userMsg = context.Message;
			std::async(std::launch::async, [=]()
			{
				auto response = SystemPing(address);
				auto message = new Messages::SendMessage(response, userMsg->Sender, userMsg->SourceProtocol);
				this->context->Messenger->Send(Messaging::MessagePointer(message));
			});

			return CommandExecutionResults(true);
		}

	}
}
