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
		 * \brief Użytkownik zażądał zatrzymania aplikacji.
		 */
		class ShutdownRequest
			: public IMessage
		{
		public:
			static const int MessageType = 4; //!< Typ wiadomości.

			/**
			 * \brief Inicializuje obiekt wiadomości.
			 */
			ShutdownRequest()
				: IMessage(MessageType)
			{ }
		};

	}
}