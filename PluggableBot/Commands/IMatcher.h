#pragma once
#include <string>
#include "ExecutionContext.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Klasy implementuj�ce ten interfejs s� odpowiedzialne za dopasowywanie tekstu do komend.
		 * S� odpowiedzialne tylko za okre�lenie, czy komenda jest, czy nie, pe�no tekstowa
		 * oraz stwierdzenie, czy komenda pasuje.
		 */
		class IMatcher
		{
		public:
			/**
			 * Okre�la, czy komenda jest pe�no tekstowa, czy nie.
			 */
			const bool IsFullText;

			/**
			 * Pr�buje dopasowa� wynik parsowania do komendy.
			 * Je�li komenda jest pe�no tekstowa(IsFullText zwraca true), implementacje tej metody
			 * powinny pracowa� na ExecutionContext::Message::FullText, je�li nie - na pozosta�ych parametrach.
			 */
			virtual bool Matches(const ExecutionContext& context) = 0;

			virtual ~IMatcher() { }

		protected:
			/**
			 * Inicjalizuje obiekt.
			 */
			IMatcher(bool isFullText = false)
				: IsFullText(isFullText)
			{ }
		};
	}
}
