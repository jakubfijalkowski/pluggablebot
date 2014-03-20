#pragma once

namespace PluggableBot
{
	namespace Messaging
	{

		/**
		 * Interfejs dla wszystkich wiadomoœci - zawiera pole Type, pozwalaj¹ce okreœliæ w³aœciwy typ
		 * wiadomoœci nie u¿ywaj¹c dynamic_cast.
		 */
		class IMessage
		{
		public:
			/**
			 * Typ wiadomoœci
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