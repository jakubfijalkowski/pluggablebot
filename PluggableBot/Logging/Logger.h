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
		 * Poziom wiadomo�ci.
		 */
		enum class LogLevel
		{
			/**
			 * Najni�szy - informacja przydatna w debugowaniu.
			 */
			Debug,

			/**
			 * Oznacza operacj� uko�czon� sukcesem.
			 */
			Information,

			/**
			 * Ostrze�enie - co� si� nie uda�o, ale nie ma to wi�kszego wp�ywu na dzia�anie aplikacji.
			 */
			Warning,

			 /**
			 * B��d - operacja si� nie uda�a, cz�� funkcjonalno�ci mo�e nie by� dost�pna, ale aplikacja
			 * dzia�a nadal.
			 */
			Error,
			
			/**
			 * B��d kt�rego nie da si� naprawi� - przerywa dzia�anie aplikacji.
			 */
			Fatal
		};

		/**
		 * Logger - s�u�y do logowania informacji z wykonywania aplikacji.
		 */
		class PLUGIN_API Logger
		{
		public:
			/**
			 * Inicjalizuje logger o wskazanej nazwie i podanymi wyj�ciami.
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
			 * Loguje tekst, kt�ry przed zapisem jest formatowany, o poziomie LogLevel::Debug.
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
			* Loguje tekst, kt�ry przed zapisem jest formatowany, o poziomie LogLevel::Information.
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
			* Loguje tekst, kt�ry przed zapisem jest formatowany, o poziomie LogLevel::Warning.
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
			* Loguje tekst, kt�ry przed zapisem jest formatowany, o poziomie LogLevel::Error.
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
			* Loguje tekst, kt�ry przed zapisem jest formatowany, o poziomie LogLevel::Fatal.
			*/
			template<typename... Args>
			void Fatal(const std::string& format, const Args&... args)
			{
				this->Log(LogLevel::Fatal, fmt::str(fmt::Format(format, args...)));
			}

			/**
			 * Loguje wiadomo�� o podanym poziomie na wszystkie wyj�cia.
			 *
			 * Metoda ta musi jest thread-safe, jako i� jest g��wn� u�ywan� do zapisu informacji,
			 * i mo�e by� wywo�ywana z wielu w�tk�w.
			 */
			void Log(LogLevel level, const std::string& message);

		private:
			std::string name;
			const std::vector<IOutput*>& outputs;
		};

		typedef std::unique_ptr<Logger> LoggerPointer;
	}
}