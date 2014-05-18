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
		 * U�ytkownik za��da� zatrzymania aplikacji.
		 */
		class ShutdownRequest
			: public IMessage
		{
		public:
			static const int MessageType = 4;

			/**
			 * Inicializuje obiekt wiadomo�ci.
			 */
			ShutdownRequest()
				: IMessage(MessageType)
			{ }
		};

	}
}