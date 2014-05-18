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
		 * Otrzymano wiadomo�� od u�ytkownika.
		 */
		class MessageReceived
			: public IMessage
		{
		public:
			static const int MessageType = 1;

			/**
			 * Wiadomo��, kt�r� otrzymano.
			 */
			const UserMessagePointer UserMessage;

			/**
			 * Inicializuje obiekt wiadomo�ci.
			 */
			MessageReceived(UserMessagePointer userMsg)
				: IMessage(MessageType), UserMessage(userMsg)
			{ }
		};

	}
}