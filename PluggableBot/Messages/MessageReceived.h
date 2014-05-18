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
		 * Otrzymano wiadomoœæ od u¿ytkownika.
		 */
		class MessageReceived
			: public IMessage
		{
		public:
			static const int MessageType = 1;

			/**
			 * Wiadomoœæ, któr¹ otrzymano.
			 */
			const UserMessagePointer UserMessage;

			/**
			 * Inicializuje obiekt wiadomoœci.
			 */
			MessageReceived(UserMessagePointer userMsg)
				: IMessage(MessageType), UserMessage(userMsg)
			{ }
		};

	}
}