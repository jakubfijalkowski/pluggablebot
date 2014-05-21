#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		/**
		 * Wyjątek mówiący o tym, że wystąpił problem z połączeniem.
		 */
		class ConnectionFailureException
			: public std::exception
		{
		public:
			/**
			 * Inicjalizuje wyjątek odpowiednią wiadomością.
			 */
			ConnectionFailureException(const std::string& message)
				: std::exception(message.c_str())
			{ }
		};

	}
}