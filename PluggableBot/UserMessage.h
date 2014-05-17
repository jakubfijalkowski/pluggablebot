#pragma once
#include <string>
#include <memory>
#include "IProtocol.h"

namespace PluggableBot
{

	/**
	 * Okre�la wiadomo�� otrzyman� od u�ytkownika.
	 */
	class UserMessage
	{
	public:
		/**
		 * Tre�� wiadomo�ci.
		 */
		const std::string Content;

		/**
		 * Okre�la, kto wys�a� wiadomo��. Mo�e to by� np. numer GG albo adres XMPP, zale�nie od tego,
		 * jakim protoko�em zosta�a wys�ana. Jest jednoznaczna, tj. wysy�aj�c odpowied� na ten adres,
		 * wiadomo�� otrzyma u�ytkownik, kt�ry wys�a� t� wiadomo��.
		 */
		const std::string Sender;

		/**
		 * Protok�, na kt�ry wiadomo�� zosta�a wys�ana.
		 */
		const ProtocolPointer SourceProtocol;

		/**
		 * Inicjalizuje wiadomo��.
		 */
		UserMessage(const std::string& content, const std::string& sender, ProtocolPointer protocol)
			: Content(content), Sender(sender), SourceProtocol(protocol)
		{ }
	};

	typedef std::shared_ptr<const UserMessage> UserMessagePointer;

}