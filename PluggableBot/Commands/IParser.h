#pragma once
#include <string>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		* Opisuje pojedynczy parametr komend zwyk�ych.
		*
		* Parametr ma format nazwa="warto��". Znaki cudzys�owu s� opcjonalne, je�li
		* warto�� komendy nie zawiera znak�w bia�ych.
		*/
		class CommandParameter
		{
		public:
			/**
			* Nazw� parametru.
			*/
			const std::wstring Name;

			/**
			* Zwraca warto�� parametru.
			*/
			const std::wstring Value;

			/**
			 * Inicjalizuje obiekt.
			 */
			CommandParameter(const std::wstring& name, const std::wstring& value)
				: Name(name), Value(value)
			{ }
		};

		/**
		* Wynik parsowania tekstu, zwracany przez parser. Zawiera nazw� oraz wszystkie parametry, kt�re uda�o si� dopasowa�.
		*/
		class CommandParseResults
		{
		public:
			/**
			* Nazw� komendy, nawet je�li by�a to komenda pe�notekstowa i nie uda�o si�
			* jej inaczej zinterpretowa�(jest to fragment do pierwszego znaku).
			*/
			const std::wstring Name;

			/**
			* Pe�ny tekst, kt�ry by� u�yty do parsowania.
			*/
			const std::wstring FullText;

			/**
			* Okre�la, czy uda�o si� dopasowa� tekst do formatu komendy zwyk�ej.
			* Je�li jest fa�szem, oznacza to, �e komenda powinna by� tylko rozwa�ana
			* jako pe�notekstowa.
			*/
			const bool IsSuccess;

			/**
			 * Inicjalizuje obiekt, kt�ry okre�la wynik parsowania komendy
			 * pe�notekstowej(IsSuccess b�dzie ustawiony na false).
			 */
			CommandParseResults(const std::wstring& name, const std::wstring& fullText)
				: Name(name), FullText(fullText), IsSuccess(false)
			{ }

			/**
			* Pobiera ilo�� parametr�w, o ile parsowanie si� uda�o.
			*/
			int GetParameterCount() const
			{

			}

			/**
			* Sprawdza, czy wynik zawiera parametr o wskazanej nazwie.
			*
			* \param name Nazwa parametru.
			*/
			bool HasParameter(const std::wstring& name) const
			{

			}

			/**
			* Pobiera parametr ze wskazanej pozycji. Je�li indeks wykracza poza zakres, zostaje rzucony
			* wyj�tek.
			*
			* \param index Indeks parametru. Musi by� z zakresu 0..GetParameterCount().
			* \exception std::out_of_range Rzucany, gdy indeks wykracza poza zakres.
			*/
			const CommandParameter& GetParameter(int index) const
			{

			}

			/* Pobiera parametr o wskazanej nazwie. Je�li nie istnieje, metoda rzuca wyj�tek.
			*
			* \param name Nazwa parametru.
			* \exception Exceptions::NotFoundException Rzucany, gdy parametr o wskazanej nazwie nie mo�e zosta� znaleziony.
			*/
			const CommandParameter& GetParameter(const std::wstring& name) const
			{

			}
		};

		/**
		 * Interfejs dla klas, odpowiedzialnych za parsowanie wiadomo�ci.
		 *
		 * Parsowanie odbywa si� poprzez pr�b� dopasowania tekstu do nast�puj�cego formatu:
		 * {nazwa_komendy} {nazwa_parametru1}="{warto��1}" {nazwa_parametru2}="{warto��2}" ...
		 * Znaki cudzys�owiu s� opcjonalne gdy warto�� nie zawiera znak�w bia�ych, w przeciwnym razie
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
			virtual CommandParseResults Parse(const std::wstring& text) = 0;
		};

	}
}