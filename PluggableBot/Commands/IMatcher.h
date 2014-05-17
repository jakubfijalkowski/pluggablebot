#pragma once
#include <string>
#include "ExecutionContext.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Klasy implementuj¹ce ten interfejs s¹ odpowiedzialne za dopasowywanie tekstu do komend.
		 * S¹ odpowiedzialne tylko za okreœlenie, czy komenda jest, czy nie, pe³no tekstowa
		 * oraz stwierdzenie, czy komenda pasuje.
		 */
		class IMatcher
		{
		public:
			/**
			 * Okreœla, czy komenda jest pe³no tekstowa, czy nie.
			 */
			const bool IsFullText;

			/**
			 * Próbuje dopasowaæ wynik parsowania do komendy.
			 * Jeœli komenda jest pe³no tekstowa(IsFullText zwraca true), implementacje tej metody
			 * powinny pracowaæ na ExecutionContext::Message::FullText, jeœli nie - na pozosta³ych parametrach.
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
