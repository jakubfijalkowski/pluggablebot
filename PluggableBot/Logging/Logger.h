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
		 * Poziom wiadomości.
		 */
		enum class LogLevel
		{
			/**
			 * Najniższy - informacja przydatna w debugowaniu.
			 */
			Debug,

			/**
			 * Oznacza operację ukończoną sukcesem.
			 */
			Information,

			/**
			 * Ostrzeżenie - coś się nie udało, ale nie ma to większego wpływu na działanie aplikacji.
			 */
			Warning,

			 /**
			 * Błąd - operacja się nie udała, część funkcjonalności może nie być dostępna, ale aplikacja
			 * działa nadal.
			 */
			Error,
			
			/**
			 * Błąd którego nie da się naprawić - przerywa działanie aplikacji.
			 */
			Fatal
		};

		/**
		 * Logger - służy do logowania informacji z wykonywania aplikacji.
		 */
		class PLUGIN_API Logger
		{
		public:
			/**
			 * Inicjalizuje logger o wskazanej nazwie i podanymi wyjściami.
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
			 * Loguje wiadomość o podanym poziomie na wszystkie wyjścia.
			 *
			 * Metoda ta musi jest thread-safe, jako iż jest główną używaną do zapisu informacji,
			 * i może być wywoływana z wielu wątków.
			 */
			void Log(LogLevel level, const std::string& message);

		private:
			std::string name;
			const std::vector<IOutput*>& outputs;
		};

		typedef std::unique_ptr<Logger> LoggerPointer;
	}
}