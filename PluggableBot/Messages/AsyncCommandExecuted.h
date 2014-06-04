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
		 * Komenda została wywołana poprawnie i zwraca użytkownikowi wynik.
		 * Asynchroniczny odpowiednik Commands::CommandExecutionResults.
		 */
		class AsyncCommandExecuted
			: public IMessage
		{
		public:
			static const int MessageType = 7;

			/**
			 * Określa, która komenda wysłała tą wiadomość.
			 */
			const Commands::CommandPointer Command;

			/**
			 * Treść wiadomości, która zostanie wysłana użytkownikowi.
			 */
			const std::string Message;

			/**
			 * Obiekt będący dodatkowymi danymi. Jest opcjonalny(może być nullptr).
			 */
			const std::shared_ptr<const jsonxx::Object> AdditionalData;

			/**
			 * Odbiorca wiadomości.
			 */
			const std::string Recipient;

			/**
			 * Określa, który protokół powinien wysłać wiadomość.
			 */
			const ProtocolPointer Protocol;

			/**
			 * Inicializuje obiekt wiadomości.
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