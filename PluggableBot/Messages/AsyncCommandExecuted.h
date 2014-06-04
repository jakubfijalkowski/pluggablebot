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
		 * \brief Komenda została wywołana poprawnie i zwraca użytkownikowi wynik.
		 * Asynchroniczny odpowiednik Commands::CommandExecutionResults.
		 */
		class AsyncCommandExecuted
			: public IMessage
		{
		public:
			static const int MessageType = 7; //!< Typ wiadomości.

			/**
			 * \brief Określa, która komenda wysłała tą wiadomość.
			 */
			const Commands::CommandPointer Command;

			/**
			 * \brief Treść wiadomości, która zostanie wysłana użytkownikowi.
			 */
			const std::string Message;

			/**
			 * \brief Obiekt będący dodatkowymi danymi. Jest opcjonalny(może być `nullptr`).
			 */
			const std::shared_ptr<const jsonxx::Object> AdditionalData;

			/**
			 * \brief Odbiorca wiadomości.
			 */
			const std::string Recipient;

			/**
			 * \brief Określa, który protokół powinien wysłać wiadomość.
			 */
			const ProtocolPointer Protocol;

			/**
			 * \brief Inicializuje obiekt wiadomości niezbędnymi informacjami.
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