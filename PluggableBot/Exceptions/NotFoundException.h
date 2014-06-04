#pragma once
#include <exception>

namespace PluggableBot
{
	namespace Exceptions
	{

		/**
		 * \brief Wyjątek rzucany, gdy nie uda się znaleźć szukanej rzeczy.
		 */
		class NotFoundException
			: public std::exception
		{
		public:
			/**
			 * \brief Inicjalizuje pusty wyjątek.
			 */
			NotFoundException()
			{ }
			
			/**
			 * \brief Inicjalizuje wyjątek wskazaną wiadomością.
			 */
			NotFoundException(const std::string& msg)
				: std::exception(msg.c_str())
			{ }
		};

	}
}