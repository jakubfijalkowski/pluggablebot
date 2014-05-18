#pragma once
#include <exception>

namespace PluggableBot
{
	namespace Exceptions
	{

		/**
		 * Wyj�tek rzucany, gdy nie uda si� znale�� szukanej rzeczy.
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