#pragma once
#include <string>
#include "CommandParseResults.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		* Klasy implementuj�ce ten interfejs s� odpowiedzialne za dopasowywanie tekstu do komend.
		* S� odpowiedzialne tylko za okre�lenie, czy komenda jest pe�no tekstowa, czy nie
		* oraz stwierdzenie, czy komenda pasuje.
		*/
		class IMatcher
		{
		public:
			/**
			 * Okre�la, czy komenda jest pe�no tekstowa, czy nie.
			 */
			virtual bool IsFullText() = 0;

			/**
			 * Pr�buje dopasowa� wynik parsowania do komendy.
			 * Je�li komenda jest pe�no tekstowa(IsFullText zwraca true), implementacje tej metody
			 * powinny pracowa� na CommandParseResult.GetFullText, je�li nie - na pozosta�ych parametrach.
			 */
			virtual bool Matches(const CommandParseResults& results) = 0;
		};

	}
}
