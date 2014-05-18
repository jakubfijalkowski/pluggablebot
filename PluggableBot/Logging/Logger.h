#pragma once
#include <string>
#include <memory>
#include <vector>
#include "../Config.h"
#include "../External/format.h"

namespace PluggableBot
{
	namespace Logging
	{
		class IOutput;

		/**
		 * Poziom wiadomoœci.
		 */
		enum class LogLevel
		{
			/**
			 * Najni¿szy - informacja przydatna w debugowaniu.
			 */
			Debug,

			/**
			 * Oznacza operacjê ukoñczon¹ sukcesem.
			 */
			Information,

			/**
			 * Ostrze¿enie - coœ siê nie uda³o, ale nie ma to wiêkszego wp³ywu na dzia³anie aplikacji.
			 */
			Warning,

			 /**
			 * B³¹d - operacja siê nie uda³a, czêœæ funkcjonalnoœci mo¿e nie byæ dostêpna, ale aplikacja
			 * dzia³a nadal.
			 */
			Error,
			
			/**
			 * B³¹d którego nie da siê naprawiæ - przerywa dzia³anie aplikacji.
			 */
			Fatal
		};

		/**
		 * Logger - s³u¿y do logowania informacji z wykonywania aplikacji.
		 */
		class PLUGIN_API Logger
		{
		public:
			/**
			 * Inicjalizuje logger o wskazanej nazwie i podanymi wyjœciami.
			 */
			Logger(const std::string& name, const std::vector<IOutput*>& outputs);

			/**
			 * Loguje informacje o poziomie LogLevel::Debug.
			 */
			void Debug(const std::string& message)
			{
				this->Log(LogLevel::Debug, message);
			}

			/**
			 * Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Debug.
			 */
			template<typename... Args>
			void Debug(const std::string& format, const Args&... args)
			{
				this->Log(LogLevel::Debug, fmt::str(fmt::Format(format, args...)));
			}

			/**
			* Loguje informacje o poziomie LogLevel::Information.
			*/
			void Information(const std::string& message)
			{
				this->Log(LogLevel::Information, message);
			}

			/**
			* Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Information.
			*/
			template<typename... Args>
			void Information(const std::string& format, const Args&... args)
			{
				this->Log(LogLevel::Information, fmt::str(fmt::Format(format, args...)));
			}

			/**
			* Loguje informacje o poziomie LogLevel::Warning.
			*/
			void Warning(const std::string& message)
			{
				this->Log(LogLevel::Warning, message);
			}

			/**
			* Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Warning.
			*/
			template<typename... Args>
			void Warning(const std::string& format, const Args&... args)
			{
				this->Log(LogLevel::Warning, fmt::str(fmt::Format(format, args...)));
			}

			/**
			* Loguje informacje o poziomie LogLevel::Error.
			*/
			void Error(const std::string& message)
			{
				this->Log(LogLevel::Error, message);
			}

			/**
			* Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Error.
			*/
			template<typename... Args>
			void Error(const std::string& format, const Args&... args)
			{
				this->Log(LogLevel::Error, fmt::str(fmt::Format(format, args...)));
			}

			/**
			* Loguje informacje o poziomie LogLevel::Fatal.
			*/
			void Fatal(const std::string& message)
			{
				this->Log(LogLevel::Fatal, message);
			}

			/**
			* Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Fatal.
			*/
			template<typename... Args>
			void Fatal(const std::string& format, const Args&... args)
			{
				this->Log(LogLevel::Fatal, fmt::str(fmt::Format(format, args...)));
			}

			/**
			 * Loguje wiadomoœæ o podanym poziomie na wszystkie wyjœcia.
			 *
			 * Metoda ta musi jest thread-safe, jako i¿ jest g³ówn¹ u¿ywan¹ do zapisu informacji,
			 * i mo¿e byæ wywo³ywana z wielu w¹tków.
			 */
			void Log(LogLevel level, const std::string& message);

		private:
			std::string name;
			const std::vector<IOutput*>& outputs;
		};

		typedef std::unique_ptr<Logger> LoggerPointer;
	}
}