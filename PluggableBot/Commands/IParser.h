#pragma once
#include <string>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		* Opisuje pojedynczy parametr komend zwyk³ych.
		*
		* Parametr ma format nazwa="wartoœæ". Znaki cudzys³owu s¹ opcjonalne, jeœli
		* wartoœæ komendy nie zawiera znaków bia³ych.
		*/
		class CommandParameter
		{
		public:
			/**
			* Nazwê parametru.
			*/
			const std::wstring Name;

			/**
			* Zwraca wartoœæ parametru.
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
		* Wynik parsowania tekstu, zwracany przez parser. Zawiera nazwê oraz wszystkie parametry, które uda³o siê dopasowaæ.
		*/
		class CommandParseResults
		{
		public:
			/**
			* Nazwê komendy, nawet jeœli by³a to komenda pe³notekstowa i nie uda³o siê
			* jej inaczej zinterpretowaæ(jest to fragment do pierwszego znaku).
			*/
			const std::wstring Name;

			/**
			* Pe³ny tekst, który by³ u¿yty do parsowania.
			*/
			const std::wstring FullText;

			/**
			* Okreœla, czy uda³o siê dopasowaæ tekst do formatu komendy zwyk³ej.
			* Jeœli jest fa³szem, oznacza to, ¿e komenda powinna byæ tylko rozwa¿ana
			* jako pe³notekstowa.
			*/
			const bool IsSuccess;

			/**
			 * Inicjalizuje obiekt, który okreœla wynik parsowania komendy
			 * pe³notekstowej(IsSuccess bêdzie ustawiony na false).
			 */
			CommandParseResults(const std::wstring& name, const std::wstring& fullText)
				: Name(name), FullText(fullText), IsSuccess(false)
			{ }

			/**
			* Pobiera iloœæ parametrów, o ile parsowanie siê uda³o.
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
			* Pobiera parametr ze wskazanej pozycji. Jeœli indeks wykracza poza zakres, zostaje rzucony
			* wyj¹tek.
			*
			* \param index Indeks parametru. Musi byæ z zakresu 0..GetParameterCount().
			* \exception std::out_of_range Rzucany, gdy indeks wykracza poza zakres.
			*/
			const CommandParameter& GetParameter(int index) const
			{

			}

			/* Pobiera parametr o wskazanej nazwie. Jeœli nie istnieje, metoda rzuca wyj¹tek.
			*
			* \param name Nazwa parametru.
			* \exception Exceptions::NotFoundException Rzucany, gdy parametr o wskazanej nazwie nie mo¿e zostaæ znaleziony.
			*/
			const CommandParameter& GetParameter(const std::wstring& name) const
			{

			}
		};

		/**
		 * Interfejs dla klas, odpowiedzialnych za parsowanie wiadomoœci.
		 *
		 * Parsowanie odbywa siê poprzez próbê dopasowania tekstu do nastêpuj¹cego formatu:
		 * {nazwa_komendy} {nazwa_parametru1}="{wartoœæ1}" {nazwa_parametru2}="{wartoœæ2}" ...
		 * Znaki cudzys³owiu s¹ opcjonalne gdy wartoœæ nie zawiera znaków bia³ych, w przeciwnym razie
		 * s¹ one obowi¹zkowe.
		 * Gdy nie uda siê dopasowaæ tekstu do w/w formatu, parser uznaje, ¿e komenda jest pe³no tekstowa
		 * i przerywa parsowanie.
		 */
		class IParser
		{
		public:
			/**
			 * Próbuje zinterpretowaæ wiadomoœæ jako komendê. Sposób parsowania jest w opisie klasy.
			 * \param text Tekst wiadomoœci. 
			 */
			virtual CommandParseResults Parse(const std::wstring& text) = 0;
		};

	}
}