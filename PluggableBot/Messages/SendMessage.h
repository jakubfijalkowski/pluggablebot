#pragma once
#include <string>
#include "../Messaging/IMessage.h"
#include "../IProtocol.h"

#ifdef SendMessage
#undef SendMessage
#endif

namespace PluggableBot
{
	namespace Messages
	{
		using namespace Messaging;

		/**
		 * Rządanie wysłania wiadomości.
		 */
		class SendMessage
			: public IMessage
		{
		public:
			static const int MessageType = 2;

			/**
			 * Wiadomość, którą otrzymano.
			 */
			const std::string Content;

			/**
			 * Odbiorca wiadomości.
			 */
			const std::string Recipient;

			/**
			 * Określa, który protokół powinien wysłać wiadomość.
			 * Jeśli jest \a {nullptr}, nie ma ograniczeń, kto powinien obsłużyć tą wiadomość.
			 */
			const IProtocol* const Protocol;

			/**
			 * Inicializuje obiekt wiadomości.
			 */
			SendMessage(const std::string& content, const std::string& recipient, const IProtocol* protocol)
				: IMessage(MessageType), Content(content), Recipient(recipient), Protocol(protocol)
			{ }
		};

	}
}