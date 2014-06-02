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
		 * Nie uda�o si� wywo�a� komendy asynchronicznie i u�ytkownik powinien otrzyma� odpowied� o b��dzie.
		 * Asynchroniczny odpowiednik Exceptions::ExecutionException.
		 */
		class AsyncExecutionFailure
			: public IMessage
		{
		public:
			static const int MessageType = 5;

			/**
			 * Okre�la, kt�ra komenda wys�a�a t� wiadomo��.
			 */
			const Commands::CommandPointer Command;

			/**
			 * Opis b��du.
			 */
			const std::string Description;

			/**
			 * Systemowy kod b��du.
			 */
			const unsigned int ErrorCode;

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