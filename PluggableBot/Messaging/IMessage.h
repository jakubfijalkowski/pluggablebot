#pragma once
#include <memory>
#include "../Config.h"

namespace PluggableBot
{
	namespace Messaging
	{

		/**
		 * Interfejs dla wszystkich wiadomoœci - zawiera pole Type, pozwalaj¹ce okreœliæ w³aœciwy typ
		 * wiadomoœci nie u¿ywaj¹c dynamic_cast.
		 */
		class PLUGIN_API IMessage
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

		typedef std::shared_ptr<IMessage> MessagePointer;

	}
}