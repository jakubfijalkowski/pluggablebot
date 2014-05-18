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
		 * Protok� przesta� dzia�a�.
		 */
		class ProtocolFailure
			: public IMessage
		{
		public:
			static const int MessageType = 3;

			/**
			 * Okre�la, kt�ry protok� przesta� dzia�a�.
			 */
			const IProtocol* const Protocol;

			/**
			 * Inicializuje obiekt wiadomo�ci.
			 */
			ProtocolFailure(const IProtocol* protocol)
				: IMessage(MessageType), Protocol(protocol)
			{ }
		};

	}
}