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
		 * Rz¹danie wys³ania wiadomoœci.
		 */
		class SendMessage
			: public IMessage
		{
		public:
			static const int MessageType = 2;

			/**
			 * Wiadomoœæ, któr¹ otrzymano.
			 */
			const std::string Content;

			/**
			 * Odbiorca wiadomoœci.
			 */
			const std::string Recipient;

			/**
			 * Okreœla, który protokó³ powinien wys³aæ wiadomoœæ.
			 * Jeœli jest \a {nullptr}, nie ma ograniczeñ, kto powinien obs³u¿yæ t¹ wiadomoœæ.
			 */
			const IProtocol* const Protocol;

			/**
			 * Inicializuje obiekt wiadomoœci.
			 */
			SendMessage(const std::string& content, const std::string& recipient, const IProtocol* protocol)
				: IMessage(MessageType), Content(content), Recipient(recipient), Protocol(protocol)
			{ }
		};

	}
}