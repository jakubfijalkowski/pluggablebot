#pragma once
#include <exception>

namespace PluggableBot
{
	namespace Exceptions
	{

		/**
		 * Wyj¹tek rzucany, gdy nie uda siê znaleŸæ szukanej rzeczy.
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