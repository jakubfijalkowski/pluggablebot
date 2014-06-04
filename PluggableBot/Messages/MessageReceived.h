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
		 * \brief Otrzymano wiadomość od użytkownika.
		 */
		class MessageReceived
			: public IMessage
		{
		public:
			static const int MessageType = 1; //!< Typ wiadomości.

			/**
			 * \brief Wiadomość, którą otrzymano.
			 */
			const UserMessagePointer UserMessage;

			/**
			 * \brief Inicializuje obiekt wiadomości niezgędnymi wartościami.
			 */
			MessageReceived(UserMessagePointer userMsg)
				: IMessage(MessageType), UserMessage(userMsg)
			{ }
		};

	}
}