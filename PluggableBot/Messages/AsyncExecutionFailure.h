#pragma once
#include <string>
#include "../Commands/ICommand.h"
#include "../Messaging/IMessage.h"
#include "../IProtocol.h"

namespace PluggableBot
{
	namespace Messages
	{
		using namespace Messaging;

		/**
		 * \brief Nie udało się wywołać komendy asynchronicznie i użytkownik powinien
		 * otrzymać odpowiedź o błędzie.
		 * Asynchroniczny odpowiednik Exceptions::ExecutionException.
		 */
		class AsyncExecutionFailure
			: public IMessage
		{
		public:
			static const int MessageType = 5; //!< Typ wiadomości.

			/**
			 * \brief Określa, która komenda wysłała tą wiadomość.
			 */
			const Commands::CommandPointer Command;

			/**
			 * \brief Opis błędu.
			 */
			const std::string Description;

			/**
			 * \brief Systemowy kod błędu.
			 */
			const unsigned int ErrorCode;

			/**
			 * \brief Odbiorca wiadomości.
			 */
			const std::string Recipient;

			/**
			 * \brief Określa, który protokół powinien wysłać wiadomość.
			 */
			const ProtocolPointer Protocol;

			/**
			 * \brief Inicializuje obiekt wiadomości niezbędnymi wartościami.
			 */
			AsyncExecutionFailure(
				const Commands::CommandPointer command,
				const std::string& description, unsigned int errorCode,
				const std::string& recipient, const ProtocolPointer protocol)
				: IMessage(MessageType), Command(command),
				  Description(description), ErrorCode(errorCode),
				  Recipient(recipient), Protocol(protocol)
			{ }
		};

	}
}