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
		 * \brief Otrzymano obrazek od użytkownika.
		 *
		 * UWAGA! Wiadomość ta może długo zalegać w obiekcie Messenger, dlatego
		 * należy ograniczać wysyłanie obrazków bez wywołania komendy zapisującej
		 * je(np. FilesystemPlugin::StoreTextCommand)!
		 */
		class ImageReceived
			: public IMessage
		{
		public:
			static const int MessageType = 6; //!< Typ wiadomości.
			
			/**
			 * \brief Dane obrazka.
			 */
			const std::unique_ptr<char[]> Data;

			/**
			 * \brief Rozmiar danych w bajtach.
			 */
			const size_t DataSize;

			/**
			 * \brief Nazwa pliku. Może być ignorowana.
			 */
			const std::string FileName;

			/**
			 * \brief Nadawca wiadomości.
			 */
			const std::string Sender;

			/**
			 * \brief Określa, z którego protokołu otrzymano wiadomość.
			 */
			const ProtocolPointer Protocol;

			/**
			 * \brief Inicializuje obiekt wiadomości niezbędnymi wartościami.
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