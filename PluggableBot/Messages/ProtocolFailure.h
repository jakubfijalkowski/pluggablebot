#pragma once
#include <string>
#include "../Messaging/IMessage.h"
#include "../IProtocol.h"

namespace PluggableBot
{
	namespace Messages
	{
		using namespace Messaging;

		/**
		 * \brief Protokół przestał działać.
		 */
		class ProtocolFailure
			: public IMessage
		{
		public:
			static const int MessageType = 3; //!< Typ wiadomości.

			/**
			 * \brief Określa, który protokół przestał działać.
			 */
			const IProtocol* const Protocol;

			/**
			 * \brief Inicializuje obiekt wiadomości niezbędnymi wartościami.
			 */
			ProtocolFailure(const IProtocol* protocol)
				: IMessage(MessageType), Protocol(protocol)
			{ }
		};

	}
}