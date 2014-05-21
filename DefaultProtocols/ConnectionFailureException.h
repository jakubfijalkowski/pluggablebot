#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		/**
		 * Wyj�tek m�wi�cy o tym, �e wyst�pi� problem z po��czeniem.
		 */
		class ConnectionFailureException
			: public std::exception
		{
		public:
			/**
			 * Inicjalizuje wyj�tek odpowiedni� wiadomo�ci�.
			 */
			ConnectionFailureException(const std::string& message)
				: std::exception(message.c_str())
			{ }
		};

	}
}