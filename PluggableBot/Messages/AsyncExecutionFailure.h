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
		 * Nie udało się wywołać komendy asynchronicznie i użytkownik powinien otrzymać odpowiedź o błędzie.
		 * Asynchroniczny odpowiednik Exceptions::ExecutionException.
		 */
		class AsyncExecutionFailure
			: public IMessage
		{
		public:
			static const int MessageType = 5;

			/**
			 * Określa, która komenda wysłała tą wiadomość.
			 */
			const Commands::CommandPointer Command;

			/**
			 * Opis błędu.
			 */
			const std::string Description;

			/**
			 * Systemowy kod błędu.
			 */
			const unsigned int ErrorCode;

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