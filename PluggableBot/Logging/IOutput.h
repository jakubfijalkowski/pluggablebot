#pragma once
#include <string>
#include <Windows.h>
#include "../Config.h"
#include "Logger.h"

namespace PluggableBot
{
	namespace Logging
	{
		
		/**
		 * Wyjście dla klasy loggera.
		 */
		class PLUGIN_API IOutput
		{
		public:
			/**
			 * Zapisuje wiadomość do wyjścia.
			 */
			virtual void Write(LogLevel level, const std::string& loggerName, const std::string& message) = 0;
		};

		/**
		 * Wyświetla wiadomości w konsoli.
		 */
		class ConsoleOutput
			: public IOutput
		{
		public:
			ConsoleOutput();
			~ConsoleOutput();

			virtual void Write(LogLevel level, const std::string& loggerName, const std::string& message);

		private:
			CRITICAL_SECTION writeLock;
			HANDLE outHandle;
		};


		/**
		 * Zapisuje wiadomości do pliku.
		 */
		class FileOutput
			: public IOutput
		{
		public:
			FileOutput(const std::string& fileName);
			~FileOutput();

			virtual void Write(LogLevel level, const std::string& loggerName, const std::string& message);

		private:
			std::string fileName;
			CRITICAL_SECTION writeLock;
		};
	}
}