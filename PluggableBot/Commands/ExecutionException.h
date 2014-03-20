#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Wyj¹tek rzucany, gdy nie uda siê wykonaæ komendy.
		 *
		 * Zawiera podstawowe informacje o b³êdzie, tj. wiadomoœæ(Message) i ewentualny kod,
		 * który jest zwracany jako dodatkowa wartoœæ.
		 */
		class ExecutionException
			: public std::exception
		{
		public:
			/**
			* Wiadomoœæ.
			*/
			const std::wstring Message;

			/**
			 * Kod b³êdu.
			 */
			const int ErrorCode;

			ExecutionException(const std::wstring& message, int errorCode = 0)
				: Message(message), ErrorCode(errorCode)
			{ }
		};

	}
}