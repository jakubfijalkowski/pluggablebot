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
		 * Interfejs dla klas, odpowiedzialnych za parsowanie wiadomości.
		 *
		 * Parsowanie odbywa się poprzez próbę dopasowania tekstu do następującego formatu:
		 * {nazwa_komendy} {nazwa_parametru1}="{wartość1}" {nazwa_parametru2}="{wartość2}" ...
		 * Znaki cudzysłowie są opcjonalne gdy wartość nie zawiera znaków białych, w przeciwnym razie
		 * są one obowiązkowe. Nazwa komendy może być w cudzysłowie, dzieki czemu może zawierać białe znaki.
		 * Znak cudzysłowu może być "wyescapeowany" znakiem \ .
		 * Gdy nie uda się dopasować tekstu do w/w formatu, parser uznaje, że komenda jest pełno tekstowa
		 * i przerywa parsowanie.
		 */
		class PLUGIN_API IParser
		{
		public:
			/**
			 * Próbuje zinterpretować wiadomość jako komendę. Sposób parsowania jest w opisie klasy.
			 * \param text Tekst wiadomości.
			 */
			virtual ParseResultsPointer Parse(const std::string& text) = 0;

			virtual ~IParser() { }
		};

		/**
		 * Domyślna implementacja IParser.
		 */
		class PLUGIN_API DefaultParser
			: public IParser
		{
		public:
			virtual ParseResultsPointer Parse(const std::string& text);
		};

	}
}