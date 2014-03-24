#pragma once
#include <string>
#include <memory>
#include "IProtocol.h"

namespace PluggableBot
{

	/**
	 * Okreœla wiadomoœæ otrzyman¹ od u¿ytkownika.
	 */
	class UserMessage
	{
	public:
		/**
		 * Treœæ wiadomoœci.
		 */
		const std::wstring Content;

		/**
		 * Okreœla, kto wys³a³ wiadomoœæ. Mo¿e to byæ np. numer GG albo adres XMPP, zale¿nie od tego,
		 * jakim protoko³em zosta³a wys³ana. Jest jednoznaczna, tj. wysy³aj¹c odpowiedŸ na ten adres,
		 * wiadomoœæ otrzyma u¿ytkownik, który wys³a³ t¹ wiadomoœæ.
		 */
		const std::wstring Sender;

		/**
		 * Protokó³, na który wiadomoœæ zosta³a wys³ana.
		 */
		const ProtocolPointer SourceProtocol;

		/**
		 * Inicjalizuje wiadomoœæ.
		 */
		UserMessage(const std::wstring& content, const std::wstring& sender, ProtocolPointer protocol)
			: Content(content), Sender(sender), SourceProtocol(protocol)
		{ }
	};

	typedef std::shared_ptr<const UserMessage> UserMessagePointer;

}