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
		 * Protokół przestał działać.
		 */
		class ProtocolFailure
			: public IMessage
		{
		public:
			static const int MessageType = 3;

			/**
			 * Określa, który protokół przestał działać.
			 */
			const IProtocol* const Protocol;

			/**
			 * Inicializuje obiekt wiadomości.
			 */
			ProtocolFailure(const IProtocol* protocol)
				: IMessage(MessageType), Protocol(protocol)
			{ }
		};

	}
}