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
		 * Komenda zosta�a wywo�ana poprawnie i zwraca u�ytkownikowi wynik.
		 * Asynchroniczny odpowiednik Commands::CommandExecutionResults.
		 */
		class AsyncCommandExecuted
			: public IMessage
		{
		public:
			static const int MessageType = 7;

			/**
			 * Okre�la, kt�ra komenda wys�a�a t� wiadomo��.
			 */
			const Commands::CommandPointer Command;

			/**
			 * Tre�� wiadomo�ci, kt�ra zostanie wys�ana u�ytkownikowi.
			 */
			const std::string Message;

			/**
			 * Obiekt b�d�cy dodatkowymi danymi. Jest opcjonalny(mo�e by� nullptr).
			 */
			const std::shared_ptr<const jsonxx::Object> AdditionalData;

			/**
			 * Odbiorca wiadomo�ci.
			 */
			const std::string Recipient;

			/**
			 * Okre�la, kt�ry protok� powinien wys�a� wiadomo��.
			 */
			const ProtocolPointer Protocol;

			/**
			 * Inicializuje obiekt wiadomo�ci.
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