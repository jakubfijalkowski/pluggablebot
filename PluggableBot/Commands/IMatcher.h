#pragma once
#include <string>
#include "CommandParseResults.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		* Klasy implementuj¹ce ten interfejs s¹ odpowiedzialne za dopasowywanie tekstu do komend.
		* S¹ odpowiedzialne tylko za okreœlenie, czy komenda jest pe³no tekstowa, czy nie
		* oraz stwierdzenie, czy komenda pasuje.
		*/
		class IMatcher
		{
		public:
			/**
			 * Okreœla, czy komenda jest pe³no tekstowa, czy nie.
			 */
			virtual bool IsFullText() = 0;

			/**
			 * Próbuje dopasowaæ wynik parsowania do komendy.
			 * Jeœli komenda jest pe³no tekstowa(IsFullText zwraca true), implementacje tej metody
			 * powinny pracowaæ na CommandParseResult.GetFullText, jeœli nie - na pozosta³ych parametrach.
			 */
			virtual bool Matches(const CommandParseResults& results) = 0;
		};

	}
}
