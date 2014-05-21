#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace Exceptions
	{

		/**
		 * Wyjątek rzucany, gdy nie uda się wykonać komendy.
		 *
		 * Zawiera podstawowe informacje o błędzie, tj. wiadomość i ewentualny kod,
		 * który jest zwracany jako dodatkowa wartość.
		 */
		class ExecutionException
			: public std::exception
		{
		public:
			/**
			 * Kod błędu.
			 */
			const int ErrorCode;

			ExecutionException(const std::string& message, int errorCode = 0)
				: std::exception(message.c_str()), ErrorCode(errorCode)
			{ }
		};

	}
}