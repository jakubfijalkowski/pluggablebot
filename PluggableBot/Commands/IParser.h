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
		 * Interfejs dla klas, odpowiedzialnych za parsowanie wiadomo�ci.
		 *
		 * Parsowanie odbywa si� poprzez pr�b� dopasowania tekstu do nast�puj�cego formatu:
		 * {nazwa_komendy} {nazwa_parametru1}="{warto��1}" {nazwa_parametru2}="{warto��2}" ...
		 * Znaki cudzys�owie s� opcjonalne gdy warto�� nie zawiera znak�w bia�ych, w przeciwnym razie
		 * s� one obowi�zkowe. Nazwa komendy mo�e by� w cudzys�owie, dzieki czemu mo�e zawiera� bia�e znaki.
		 * Znak cudzys�owu mo�e by� "wyescapeowany" znakiem \ .
		 * Gdy nie uda si� dopasowa� tekstu do w/w formatu, parser uznaje, �e komenda jest pe�no tekstowa
		 * i przerywa parsowanie.
		 */
		class PLUGIN_API IParser
		{
		public:
			/**
			 * Pr�buje zinterpretowa� wiadomo�� jako komend�. Spos�b parsowania jest w opisie klasy.
			 * \param text Tekst wiadomo�ci.
			 */
			virtual ParseResultsPointer Parse(const std::string& text) = 0;

			virtual ~IParser() { }
		};

		/**
		 * Domy�lna implementacja IParser.
		 */
		class PLUGIN_API DefaultParser
			: public IParser
		{
		public:
			virtual ParseResultsPointer Parse(const std::string& text);
		};

	}
}