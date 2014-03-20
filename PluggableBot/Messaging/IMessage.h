#pragma once

namespace PluggableBot
{
	namespace Messaging
	{

		/**
		 * Interfejs dla wszystkich wiadomo�ci - zawiera pole Type, pozwalaj�ce okre�li� w�a�ciwy typ
		 * wiadomo�ci nie u�ywaj�c dynamic_cast.
		 */
		class IMessage
		{
		public:
			/**
			 * Typ wiadomo�ci
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