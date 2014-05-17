#include <fstream>
#include <ctime>
#include "IOutput.h"

namespace PluggableBot
{
	namespace Logging
	{

		static std::string LevelStrings[(int)LogLevel::Fatal + 1];

		void InitLevelStrings()
		{
			if (LevelStrings[0].empty())
			{
				LevelStrings[(int)LogLevel::Debug] = "[Debug]";
				LevelStrings[(int)LogLevel::Information] = "[Info]";
				LevelStrings[(int)LogLevel::Warning] = "[Warn]";
				LevelStrings[(int)LogLevel::Error] = "[Error]";
				LevelStrings[(int)LogLevel::Fatal] = "[Fatal]";
			}
		}

		std::string FormatTime()
		{
			char time_buf[9];
			time_t now;
			tm tm;
			time(&now);
			localtime_s(&tm, &now);
			strftime(time_buf, 9, "%H:%M:%S", &tm);
			return time_buf;
		}

		std::string FormatDate()
		{
			char time_buf[11];
			time_t now;
			tm tm;
			time(&now);
			localtime_s(&tm, &now);
			strftime(time_buf, 11, "%Y-%m-%d", &tm);
			return time_buf;
		}

		ConsoleOutput::ConsoleOutput()
			: outHandle(nullptr)
		{
			InitLevelStrings();

			InitializeCriticalSection(&this->writeLock);
			this->outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		ConsoleOutput::~ConsoleOutput()
		{
			DeleteCriticalSection(&this->writeLock);
		}

		void ConsoleOutput::Write(LogLevel level, const std::string& loggerName, const std::string& message)
		{
			if (this->outHandle != nullptr)
			{
				EnterCriticalSection(&this->writeLock);
				switch (level)
				{
				case LogLevel::Debug:
					SetConsoleTextAttribute(this->outHandle, FOREGROUND_INTENSITY);
					break;
				case LogLevel::Warning:
					SetConsoleTextAttribute(this->outHandle, FOREGROUND_RED | FOREGROUND_GREEN);
					break;
				case LogLevel::Error:
					SetConsoleTextAttribute(this->outHandle, FOREGROUND_RED);
					break;
				case LogLevel::Fatal:
					SetConsoleTextAttribute(this->outHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
					break;
				}
				DWORD written;
				WriteConsole(this->outHandle, "[", 1, &written, nullptr);
				WriteConsole(this->outHandle, loggerName.c_str(), loggerName.length(), &written, nullptr);
				WriteConsole(this->outHandle, "]", 1, &written, nullptr);
				WriteConsole(this->outHandle, LevelStrings[(int)level].c_str(), LevelStrings[(int)level].length(), &written, nullptr);
				WriteConsole(this->outHandle, " ", 1, &written, nullptr);
				WriteConsole(this->outHandle, message.c_str(), message.length(), &written, nullptr);
				WriteConsole(this->outHandle, "\n", 1, &written, nullptr);
				SetConsoleTextAttribute(this->outHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				LeaveCriticalSection(&this->writeLock);
			}
		}

		FileOutput::FileOutput(const std::string& fileName)
			: fileName(fileName)
		{
			InitLevelStrings();
			InitializeCriticalSection(&this->writeLock);
		}

		FileOutput::~FileOutput()
		{
			DeleteCriticalSection(&this->writeLock);
		}

		void FileOutput::Write(LogLevel level, const std::string& loggerName,  const std::string& message)
		{
			EnterCriticalSection(&this->writeLock);
			std::ofstream(this->fileName, std::ofstream::app | std::ofstream::out)
				<< "[" << FormatDate() << " " << FormatTime() << "]"
				<< "[" << loggerName << "]"
				<< LevelStrings[(int)level] << " "
				<< message << std::endl;
			LeaveCriticalSection(&this->writeLock);
		}

	}
}