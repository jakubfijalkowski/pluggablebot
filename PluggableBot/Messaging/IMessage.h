#pragma once
#include <memory>
#include "../Config.h"

namespace PluggableBot
{
	namespace Messaging
	{

		/**
		 * \brief Interfejs dla wszystkich wiadomości wymienianych w aplikacji.
		 * Zawiera pole Type, pozwalające określić właściwy typ wiadomości nie używając
		 * `dynamic_cast`.
		 */
		class PLUGIN_API IMessage
		{
		public:
			/**
			 * \brief Typ wiadomości
			 */
			const int Type;

			virtual ~IMessage() { }

		protected:
			/**
			 * \brief Inicjalizuje obiekt jego typem.
			 */
			IMessage(int type)
				: Type(type)
			{ }
		};

		/**
		 * \brief Wskaźnik na wiadomość, którym posługuje się aplikacja.
		 */
		typedef std::shared_ptr<IMessage> MessagePointer;

	}
}