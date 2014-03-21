#pragma once
#include <string>

namespace PluggableBot
{
	namespace Logging
	{

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
			 * Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Debug.
			 */
			template<typename... Args>
			void Debug(const std::wstring& foramt, const Args&... args)
			{

			}

			/**
			* Loguje informacje o poziomie LogLevel::Information.
			*/
			void Information(const std::wstring& message)
			{
				this->Log(LogLevel::Information, message);
			}

			/**
			* Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Information.
			*/
			template<typename... Args>
			void Information(const std::wstring& foramt, const Args&... args)
			{

			}

			/**
			* Loguje informacje o poziomie LogLevel::Warning.
			*/
			void Warning(const std::wstring& message)
			{
				this->Log(LogLevel::Warning, message);
			}

			/**
			* Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Warning.
			*/
			template<typename... Args>
			void Warning(const std::wstring& foramt, const Args&... args)
			{

			}

			/**
			* Loguje informacje o poziomie LogLevel::Error.
			*/
			void Error(const std::wstring& message)
			{
				this->Log(LogLevel::Error, message);
			}

			/**
			* Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Error.
			*/
			template<typename... Args>
			void Error(const std::wstring& foramt, const Args&... args)
			{

			}

			/**
			* Loguje informacje o poziomie LogLevel::Fatal.
			*/
			void Fatal(const std::wstring& message)
			{
				this->Log(LogLevel::Fatal, message);
			}

			/**
			* Loguje tekst, który przed zapisem jest formatowany, o poziomie LogLevel::Fatal.
			*/
			template<typename... Args>
			void Fatal(const std::wstring& foramt, const Args&... args)
			{

			}

			/**
			 * Loguje informacje o podanym poziomie.
			 *
			 * Metoda ta musi byæ thread-safe, jako i¿ jest g³ówn¹ u¿ywan¹ do zapisu informacji,
			 * i mo¿e byæ wywo³ywana z wielu w¹tków.
			 */
			virtual void Log(LogLevel level, const std::wstring& message) = 0;

			~ILogger() { }
		};

	}
}