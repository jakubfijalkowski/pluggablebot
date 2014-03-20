#pragma once
#include "CommandParseResults.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Klasa odpowiedzialna za parsowanie wiadomo�ci pod k�tem komend.
		 *
		 * Parsowanie odbywa si� poprzez pr�b� dopasowania tekstu do nast�puj�cego formatu:
		 * {nazwa_komendy} {nazwa_parametru1}="{warto��1}" {nazwa_parametru2}="{warto��2}" ...
		 * Znaki cudzys�owiu s� opcjonalne gdy warto�� nie zawiera znak�w bia�ych, w przeciwnym razie
		 * s� one obowi�zkowe.
		 * Gdy nie uda si� dopasowa� tekstu do w/w formatu, parser uznaje, �e komenda jest pe�no tekstowa
		 * i przerywa parsowanie.
		 */
		class Parser
		{
		public:
			/**
			 * Pr�buje zinterpretowa� wiadomo�� jako komend�. Spos�b parsowania jest w opisie klasy.
			 * \param text Tekst wiadomo�ci. 
			 */
			CommandParseResults Parse(const std::wstring& text) const
			{

			}
		};

	}
}