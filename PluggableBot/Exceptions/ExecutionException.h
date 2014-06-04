#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{

	/**
	 * \brief Przestrzeń nazw zawierająca wyjątki używane przez aplikację.
	 */
	namespace Exceptions
	{

		/**
		 * \brief Wyjątek rzucany, gdy nie uda się wykonać komendy.
		 *
		 * Zawiera podstawowe informacje o błędzie, tj. wiadomość i ewentualny kod,
		 * który jest zwracany jako dodatkowa wartość.
		 */
		class ExecutionException
			: public std::exception
		{
		public:
			/**
			 * \brief Kod błędu.
			 */
			const int ErrorCode;

			/**
			 * \brief Inicjalizuje wyjątek niezbędnymi informacjami.
			 */
			ExecutionException(const std::string& message, int errorCode = 0)
				: std::exception(message.c_str()), ErrorCode(errorCode)
			{ }
		};

	}
}