#pragma once
#include <string>
#include <memory>
#include <map>
#include "ParseResults.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Interfejs dla klas, odpowiedzialnych za parsowanie wiadomo�ci.
		 *
		 * Parsowanie odbywa si� poprzez pr�b� dopasowania tekstu do nast�puj�cego formatu:
		 * {nazwa_komendy} {nazwa_parametru1}="{warto��1}" {nazwa_parametru2}="{warto��2}" ...
		 * Znaki cudzys�owie s� opcjonalne gdy warto�� nie zawiera znak�w bia�ych, w przeciwnym razie
		 * s� one obowi�zkowe.
		 * Gdy nie uda si� dopasowa� tekstu do w/w formatu, parser uznaje, �e komenda jest pe�no tekstowa
		 * i przerywa parsowanie.
		 */
		class IParser
		{
		public:
			/**
			 * Pr�buje zinterpretowa� wiadomo�� jako komend�. Spos�b parsowania jest w opisie klasy.
			 * \param text Tekst wiadomo�ci.
			 */
			virtual ParseResultsPointer Parse(const std::wstring& text) = 0;

			virtual ~IParser() { }
		};

	}
}