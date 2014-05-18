#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace Exceptions
	{

		/**
		 * Wyj¹tek rzucany, gdy nie uda siê wykonaæ komendy.
		 *
		 * Zawiera podstawowe informacje o b³êdzie, tj. wiadomoœæ i ewentualny kod,
		 * który jest zwracany jako dodatkowa wartoœæ.
		 */
		class ExecutionException
			: public std::exception
		{
		public:
			/**
			 * Kod b³êdu.
			 */
			const int ErrorCode;

			ExecutionException(const std::string& message, int errorCode = 0)
				: std::exception(message.c_str()), ErrorCode(errorCode)
			{ }
		};

	}
}