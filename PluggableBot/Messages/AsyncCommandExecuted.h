#pragma once
#include <string>
#include <memory>
#include "../Commands/ICommand.h"
#include "../Messaging/IMessage.h"
#include "../IProtocol.h"
#include "../External/jsonxx.h"

namespace PluggableBot
{
	namespace Messages
	{
		using namespace Messaging;

		/**
		 * Komenda zosta³a wywo³ana poprawnie i zwraca u¿ytkownikowi wynik.
		 * Asynchroniczny odpowiednik Commands::CommandExecutionResults.
		 */
		class AsyncCommandExecuted
			: public IMessage
		{
		public:
			static const int MessageType = 7;

			/**
			 * Okreœla, która komenda wys³a³a t¹ wiadomoœæ.
			 */
			const Commands::CommandPointer Command;

			/**
			 * Treœæ wiadomoœci, która zostanie wys³ana u¿ytkownikowi.
			 */
			const std::string Message;

			/**
			 * Obiekt bêd¹cy dodatkowymi danymi. Jest opcjonalny(mo¿e byæ nullptr).
			 */
			const std::shared_ptr<const jsonxx::Object> AdditionalData;

			/**
			 * Odbiorca wiadomoœci.
			 */
			const std::string Recipient;

			/**
			 * Okreœla, który protokó³ powinien wys³aæ wiadomoœæ.
			 */
			const ProtocolPointer Protocol;

			/**
			 * Inicializuje obiekt wiadomoœci.
			 */
			AsyncCommandExecuted(
				const Commands::CommandPointer command,
				const std::string& message, std::shared_ptr<const jsonxx::Object> additionalData,
				const std::string& recipient, const ProtocolPointer protocol)
				: IMessage(MessageType), Command(command),
				Message(message), AdditionalData(additionalData),
				Recipient(recipient), Protocol(protocol)
			{ }
		};

	}
}