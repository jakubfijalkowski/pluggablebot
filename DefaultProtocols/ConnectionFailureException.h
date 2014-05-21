#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		/**
		 * Wyj¹tek mówi¹cy o tym, ¿e wyst¹pi³ problem z po³¹czeniem.
		 */
		class ConnectionFailureException
			: public std::exception
		{
		public:
			/**
			 * Inicjalizuje wyj¹tek odpowiedni¹ wiadomoœci¹.
			 */
			ConnectionFailureException(const std::string& message)
				: std::exception(message.c_str())
			{ }
		};

	}
}