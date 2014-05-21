#pragma once
#include <exception>

namespace PluggableBot
{
	namespace Exceptions
	{

		/**
		 * Wyjątek rzucany, gdy nie uda się znaleźć szukanej rzeczy.
		 */
		class NotFoundException
			: public std::exception
		{
		public:
			NotFoundException()
			{ }

			NotFoundException(const std::string& msg)
				: std::exception(msg.c_str())
			{ }
		};

	}
}