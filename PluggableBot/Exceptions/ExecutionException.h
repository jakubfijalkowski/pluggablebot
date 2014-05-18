#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace Exceptions
	{

		/**
		 * Wyj�tek rzucany, gdy nie uda si� wykona� komendy.
		 *
		 * Zawiera podstawowe informacje o b��dzie, tj. wiadomo�� i ewentualny kod,
		 * kt�ry jest zwracany jako dodatkowa warto��.
		 */
		class ExecutionException
			: public std::exception
		{
		public:
			/**
			 * Kod b��du.
			 */
			const int ErrorCode;

			ExecutionException(const std::string& message, int errorCode = 0)
				: std::exception(message.c_str()), ErrorCode(errorCode)
			{ }
		};

	}
}