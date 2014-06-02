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
		 * Nie uda³o siê wywo³aæ komendy asynchronicznie i u¿ytkownik powinien otrzymaæ odpowiedŸ o b³êdzie.
		 * Asynchroniczny odpowiednik Exceptions::ExecutionException.
		 */
		class AsyncExecutionFailure
			: public IMessage
		{
		public:
			static const int MessageType = 5;

			/**
			 * Okreœla, która komenda wys³a³a t¹ wiadomoœæ.
			 */
			const Commands::CommandPointer Command;

			/**
			 * Opis b³êdu.
			 */
			const std::string Description;

			/**
			 * Systemowy kod b³êdu.
			 */
			const unsigned int ErrorCode;

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