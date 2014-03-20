#pragma once
#include "CommandParseResults.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Klasa odpowiedzialna za parsowanie wiadomoœci pod k¹tem komend.
		 *
		 * Parsowanie odbywa siê poprzez próbê dopasowania tekstu do nastêpuj¹cego formatu:
		 * {nazwa_komendy} {nazwa_parametru1}="{wartoœæ1}" {nazwa_parametru2}="{wartoœæ2}" ...
		 * Znaki cudzys³owiu s¹ opcjonalne gdy wartoœæ nie zawiera znaków bia³ych, w przeciwnym razie
		 * s¹ one obowi¹zkowe.
		 * Gdy nie uda siê dopasowaæ tekstu do w/w formatu, parser uznaje, ¿e komenda jest pe³no tekstowa
		 * i przerywa parsowanie.
		 */
		class Parser
		{
		public:
			/**
			 * Próbuje zinterpretowaæ wiadomoœæ jako komendê. Sposób parsowania jest w opisie klasy.
			 * \param text Tekst wiadomoœci. 
			 */
			CommandParseResults Parse(const std::wstring& text) const
			{

			}
		};

	}
}