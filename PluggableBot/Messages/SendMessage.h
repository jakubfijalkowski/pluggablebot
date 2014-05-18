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
		 * Rz�danie wys�ania wiadomo�ci.
		 */
		class SendMessage
			: public IMessage
		{
		public:
			static const int MessageType = 2;

			/**
			 * Wiadomo��, kt�r� otrzymano.
			 */
			const std::string Content;

			/**
			 * Odbiorca wiadomo�ci.
			 */
			const std::string Recipient;

			/**
			 * Okre�la, kt�ry protok� powinien wys�a� wiadomo��.
			 * Je�li jest \a {nullptr}, nie ma ogranicze�, kto powinien obs�u�y� t� wiadomo��.
			 */
			const IProtocol* const Protocol;

			/**
			 * Inicializuje obiekt wiadomo�ci.
			 */
			SendMessage(const std::string& content, const std::string& recipient, const IProtocol* protocol)
				: IMessage(MessageType), Content(content), Recipient(recipient), Protocol(protocol)
			{ }
		};

	}
}