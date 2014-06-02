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
		 * Otrzymano obrazek od użytkownika.
		 */
		class ImageReceived
			: public IMessage
		{
		public:
			static const int MessageType = 6;
			
			/**
			 * Dane obrazka.
			 */
			const std::unique_ptr<char[]> Data;

			/**
			 * Rozmiar danych.
			 */
			const size_t DataSize;

			/**
			 * Nazwa pliku. Może być ignorowane.
			 */
			const std::string FileName;

			/**
			 * Nadawca wiadomości.
			 */
			const std::string Sender;

			/**
			 * Określa, z któego protokołu otrzymano wiadomość.
			 */
			const ProtocolPointer Protocol;

			/**
			 * Inicializuje obiekt wiadomości.
			 */
			ImageReceived(
				std::unique_ptr<char[]> data, size_t dataSize, const std::string& filename,
				const std::string& sender, const ProtocolPointer protocol)
				: IMessage(MessageType), 
				Data(std::move(data)), DataSize(dataSize), FileName(filename),
				Sender(sender), Protocol(protocol)
			{ }
		};

	}
}