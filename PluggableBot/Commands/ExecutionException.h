#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Wyj�tek rzucany, gdy nie uda si� wykona� komendy.
		 *
		 * Zawiera podstawowe informacje o b��dzie, tj. wiadomo��(Message) i ewentualny kod,
		 * kt�ry jest zwracany jako dodatkowa warto��.
		 */
		class ExecutionException
			: public std::exception
		{
		public:
			/**
			* Wiadomo��.
			*/
			const std::wstring Message;

			/**
			 * Kod b��du.
			 */
			const int ErrorCode;

			ExecutionException(const std::wstring& message, int errorCode = 0)
				: Message(message), ErrorCode(errorCode)
			{ }
		};

	}
}