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
		 * Protokó³ przesta³ dzia³aæ.
		 */
		class ProtocolFailure
			: public IMessage
		{
		public:
			static const int MessageType = 3;

			/**
			 * Okreœla, który protokó³ przesta³ dzia³aæ.
			 */
			const IProtocol* const Protocol;

			/**
			 * Inicializuje obiekt wiadomoœci.
			 */
			ProtocolFailure(const IProtocol* protocol)
				: IMessage(MessageType), Protocol(protocol)
			{ }
		};

	}
}