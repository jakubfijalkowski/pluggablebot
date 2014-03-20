#pragma once
#include <string>

namespace PluggableBot
{
	namespace Logging
	{

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
		class ILogger
		{
		public:

			/**
			 * Loguje informacje o poziomie LogLevel::Debug.
			 */
			void Debug(const std::wstring& message)
			{
				this->Log(LogLevel::Debug, message);
			}

			/**
			* Loguje informacje o poziomie LogLevel::Information.
			*/
			void Information(const std::wstring& message)
			{
				this->Log(LogLevel::Information, message);
			}

			/**
			* Loguje informacje o poziomie LogLevel::Warning.
			*/
			void Warning(const std::wstring& message)
			{
				this->Log(LogLevel::Warning, message);
			}

			/**
			* Loguje informacje o poziomie LogLevel::Error.
			*/
			void Error(const std::wstring& message)
			{
				this->Log(LogLevel::Error, message);
			}

			/**
			* Loguje informacje o poziomie LogLevel::Fatal.
			*/
			void Fatal(const std::wstring& message)
			{
				this->Log(LogLevel::Fatal, message);
			}

			/**
			 * Loguje informacje o podanym poziomie.
			 *
			 * Metoda ta musi by� thread-safe, jako i� jest g��wn� u�ywan� do zapisu informacji,
			 * i mo�e by� wywo�ywana z wielu w�tk�w.
			 */
			virtual void Log(LogLevel level, const std::wstring& message) = 0;

			~ILogger() { }
		};

	}
}