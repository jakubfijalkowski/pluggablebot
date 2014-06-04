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
		 * \brief Rządanie wysłania wiadomości przez odpowiedni protokół.
		 */
		class SendMessage
			: public IMessage
		{
		public:
			static const int MessageType = 2; //!< Typ wiadomości.

			/**
			 * \brief Wiadomość tekstowa, która ma zostać wysłana.
			 */
			const std::string Content;

			/**
			 * \brief Odbiorca wiadomości.
			 */
			const std::string Recipient;

			/**
			 * \brief Określa, który protokół powinien wysłać wiadomość.
			 */
			const ProtocolPointer Protocol;

			/**
			 * \brief  Inicializuje obiekt wiadomości niezbędnymi wartościami.
			 */
			SendMessage(const std::string& content, const std::string& recipient, const ProtocolPointer protocol)
				: IMessage(MessageType), Content(content), Recipient(recipient), Protocol(protocol)
			{ }
		};

	}
}