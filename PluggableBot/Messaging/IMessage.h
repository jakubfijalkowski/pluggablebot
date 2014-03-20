#pragma once

namespace PluggableBot
{
	namespace Messaging
	{

		/**
		 * Interfejs dla wszystkich wiadomości - zawiera pole Type, pozwalające określić właściwy typ
		 * wiadomości nie używając dynamic_cast.
		 */
		class IMessage
		{
		public:
			/**
			 * Typ wiadomości
			 */
			const int Type;

			virtual ~IMessage() { }

		protected:
			/**
			 * Inicjalizuje obiekt jego typem.
			 */
			IMessage(int type)
				: Type(type)
			{ }
		};

	}
}