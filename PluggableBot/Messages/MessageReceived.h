#pragma once
#include <string>
#include "../Messaging/IMessage.h"
#include "../UserMessage.h"

namespace PluggableBot
{
	namespace Messages
	{
		using namespace Messaging;

		/**
		 * Otrzymano wiadomość od użytkownika.
		 */
		class MessageReceived
			: public IMessage
		{
		public:
			static const int MessageType = 1;

			/**
			 * Wiadomość, którą otrzymano.
			 */
			const UserMessagePointer UserMessage;

			/**
			 * Inicializuje obiekt wiadomości.
			 */
			MessageReceived(UserMessagePointer userMsg)
				: IMessage(MessageType), UserMessage(userMsg)
			{ }
		};

	}
}