#pragma once
#include <string>
#include <memory>
#include "Config.h"
#include "IProtocol.h"

namespace PluggableBot
{

	/**
	 * Określa wiadomość otrzymaną od użytkownika.
	 */
	class PLUGIN_API UserMessage
	{
	public:
		/**
		 * Treść wiadomości.
		 */
		const std::string Content;

		/**
		 * Określa, kto wysłał wiadomość. Może to być np. numer GG albo adres XMPP, zależnie od tego,
		 * jakim protokołem została wysłana. Jest jednoznaczna, tj. wysyłając odpowiedź na ten adres,
		 * wiadomość otrzyma użytkownik, który wysłał tą wiadomość.
		 */
		const std::string Sender;

		/**
		 * Protokół, na który wiadomość została wysłana.
		 */
		const ProtocolPointer SourceProtocol;

		/**
		 * Inicjalizuje wiadomość.
		 */
		UserMessage(const std::string& content, const std::string& sender, ProtocolPointer protocol)
			: Content(content), Sender(sender), SourceProtocol(protocol)
		{ }
	};

	typedef std::shared_ptr<const UserMessage> UserMessagePointer;

}