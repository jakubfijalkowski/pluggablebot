#pragma once
#include <string>
#include <memory>
#include <map>
#include "../Config.h"
#include "ParseResults.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Interfejs dla klas, odpowiedzialnych za parsowanie wiadomoœci.
		 *
		 * Parsowanie odbywa siê poprzez próbê dopasowania tekstu do nastêpuj¹cego formatu:
		 * {nazwa_komendy} {nazwa_parametru1}="{wartoœæ1}" {nazwa_parametru2}="{wartoœæ2}" ...
		 * Znaki cudzys³owie s¹ opcjonalne gdy wartoœæ nie zawiera znaków bia³ych, w przeciwnym razie
		 * s¹ one obowi¹zkowe. Nazwa komendy mo¿e byæ w cudzys³owie, dzieki czemu mo¿e zawieraæ bia³e znaki.
		 * Znak cudzys³owu mo¿e byæ "wyescapeowany" znakiem \ .
		 * Gdy nie uda siê dopasowaæ tekstu do w/w formatu, parser uznaje, ¿e komenda jest pe³no tekstowa
		 * i przerywa parsowanie.
		 */
		class PLUGIN_API IParser
		{
		public:
			/**
			 * Próbuje zinterpretowaæ wiadomoœæ jako komendê. Sposób parsowania jest w opisie klasy.
			 * \param text Tekst wiadomoœci.
			 */
			virtual ParseResultsPointer Parse(const std::string& text) = 0;

			virtual ~IParser() { }
		};

		/**
		 * Domyœlna implementacja IParser.
		 */
		class PLUGIN_API DefaultParser
			: public IParser
		{
		public:
			virtual ParseResultsPointer Parse(const std::string& text);
		};

	}
}