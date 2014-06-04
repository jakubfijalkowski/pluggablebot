#pragma once
#include <string>
#include <memory>
#include "Config.h"
#include "IProtocol.h"

namespace PluggableBot
{

	/**
	 * \brief Wiadomość otrzymana od użytkownika.
	 */
	class PLUGIN_API UserMessage
	{
	public:
		/**
		 * \brief Treść wiadomości.
		 */
		const std::string Content;

		/**
		 * \brief Określa, kto wysłał wiadomość.
		 *
		 * Może to być np. numer GG albo adres XMPP, zależnie od tego, jakim protokołem
		 * została wysłana. Jest jednoznaczna, tj. wysyłając odpowiedź na ten adres,
		 * wiadomość otrzyma użytkownik, który wysłał tą wiadomość.
		 */
		const std::string Sender;

		/**
		 * \brief Protokół, który odebrał wiadomość.
		 */
		const ProtocolPointer SourceProtocol;

		/**
		 * \brief Inicjalizuje wiadomość.
		 */
		UserMessage(const std::string& content, const std::string& sender, ProtocolPointer protocol)
			: Content(content), Sender(sender), SourceProtocol(protocol)
		{ }
	};

	/**
	 * \brief Wskaźnik na wiadomość od użytkownika
	 */
	typedef std::shared_ptr<const UserMessage> UserMessagePointer;

}