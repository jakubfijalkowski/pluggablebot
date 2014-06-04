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
		 * \brief Wyjście dla klasy loggera.
		 */
		class PLUGIN_API IOutput
		{
		public:
			/**
			 * \brief Zamyka wyjście.
			 */
			virtual ~IOutput();

			/**
			 * \brief Zapisuje wiadomość o podanym poziomie, od wskazanego Logger i o podanej treści.
			 * Nie przeprowadza żadnego formatowania.
			 */
			virtual void Write(LogLevel level, const std::string& loggerName, const std::string& message) = 0;
		};

		/**
		 * \brief Wyświetla wiadomości w konsoli.
		 * Jest *thread-safe*.
		 */
		class ConsoleOutput
			: public IOutput
		{
		public:
			/**
			 * \brief Otwiera konsolę i przygotowuje ją do zapisu.
			 */
			ConsoleOutput();

			/**
			 * \brief Zamyka konsolę.
			 */
			~ConsoleOutput();

			/**
			 * \brief Zapisuje log do konsoli.
			 */
			virtual void Write(LogLevel level, const std::string& loggerName, const std::string& message);

		private:
			CRITICAL_SECTION writeLock;
			HANDLE outHandle;
		};


		/**
		 * \brief Zapisuje wiadomości do pliku.
		 * Jest *thread-safe*.
		 *
		 * Logi zapisywane są "jeden na raz", otwierając, *flushując* i zamykając plik
		 * przy każdej wiadomości.
		 */
		class FileOutput
			: public IOutput
		{
		public:
			/**
			 * \brief Inicjalizuje wyjście.
			 */
			FileOutput(const std::string& fileName);
			
			/**
			 * \brief Czyści wyjscie.
			 */
			~FileOutput();

			/**
			* \brief Zapisuje log do konsoli.
			*/
			virtual void Write(LogLevel level, const std::string& loggerName, const std::string& message);

		private:
			std::string fileName;
			CRITICAL_SECTION writeLock;
		};
	}
}