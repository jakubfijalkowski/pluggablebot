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
		const std::wstring Content;

		/**
		 * Okre�la, kto wys�a� wiadomo��. Mo�e to by� np. numer GG albo adres XMPP, zale�nie od tego,
		 * jakim protoko�em zosta�a wys�ana. Jest jednoznaczna, tj. wysy�aj�c odpowied� na ten adres,
		 * wiadomo�� otrzyma u�ytkownik, kt�ry wys�a� t� wiadomo��.
		 */
		const std::wstring Sender;

		/**
		 * Protok�, na kt�ry wiadomo�� zosta�a wys�ana.
		 */
		const ProtocolPointer SourceProtocol;

		/**
		 * Inicjalizuje wiadomo��.
		 */
		UserMessage(const std::wstring& content, const std::wstring& sender, ProtocolPointer protocol)
			: Content(content), Sender(sender), SourceProtocol(protocol)
		{ }
	};

	typedef std::shared_ptr<const UserMessage> UserMessagePointer;

}