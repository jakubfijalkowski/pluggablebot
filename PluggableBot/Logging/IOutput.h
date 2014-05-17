#pragma once
#include <string>
#include <Windows.h>
#include "Logger.h"

namespace PluggableBot
{
	namespace Logging
	{
		
		/**
		 * Wyj�cie dla klasy loggera.
		 */
		class IOutput
		{
		public:
			/**
			 * Zapisuje wiadomo�� do wyj�cia.
			 */
			virtual void Write(LogLevel level, const std::string& loggerName, const std::string& message) = 0;
		};

		/**
		 * Wy�wietla wiadomo�ci w konsoli.
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
		 * Zapisuje wiadomo�ci do pliku.
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