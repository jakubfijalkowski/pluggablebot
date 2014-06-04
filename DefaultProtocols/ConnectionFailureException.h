#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		/**
		 * \brief Wyjątek mówiący o tym, że wystąpił problem z połączeniem.
		 */
		class ConnectionFailureException
			: public std::exception
		{
		public:
			/**
			 * \brief Inicjalizuje wyjątek odpowiednią wiadomością.
			 */
			ConnectionFailureException(const std::string& message)
				: std::exception(message.c_str())
			{ }
		};

	}
}