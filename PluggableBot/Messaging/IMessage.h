#pragma once
#include <memory>
#include "../Config.h"

namespace PluggableBot
{
	namespace Messaging
	{

		/**
		 * Interfejs dla wszystkich wiadomo�ci - zawiera pole Type, pozwalaj�ce okre�li� w�a�ciwy typ
		 * wiadomo�ci nie u�ywaj�c dynamic_cast.
		 */
		class PLUGIN_API IMessage
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

		typedef std::shared_ptr<IMessage> MessagePointer;

	}
}