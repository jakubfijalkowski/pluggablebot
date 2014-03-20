#pragma once
#include <string>
#include <memory>
#include <map>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		* Wynik parsowania tekstu, zwracany przez parser. Zawiera nazwê oraz wszystkie parametry, które uda³o siê dopasowaæ.
		*/
		class CommandParseResults
		{
		public:
			/**
			 * Typ listy parametrów(w³aœciwej).
			 */
			typedef std::map<std::wstring, std::wstring> ParameterList;

			/**
			 * Typ u¿ywany do przechowywania i przekazywania listy parametrów.
			 */
			typedef std::shared_ptr<ParameterList> ParametersPointer;

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
			* Inicjalizuje obiekt, który okreœla wynik parsowania zwyk³ej komendy.
			*/
			CommandParseResults(const std::wstring& name, const std::wstring& fullText, ParametersPointer parameters)
				: Name(name), FullText(fullText), IsSuccess(true), Parameters(parameters)
			{ }

			/**
			* Pobiera iloœæ parametrów, o ile parsowanie siê uda³o.
			*/
			int GetParameterCount() const
			{
				return this->Parameters->size();
			}

			/**
			* Sprawdza, czy wynik zawiera parametr o wskazanej nazwie.
			*
			* \param name Nazwa parametru.
			*/
			bool HasParameter(const std::wstring& name) const
			{
				return this->Parameters->find(name) != this->Parameters->end();
			}

			/**
			 * Pobiera wartoœæ parametru o wskazanej nazwie. Jeœli nie istnieje, metoda rzuca wyj¹tek.
			 *
			 * \param name Nazwa parametru.
			 * \exception Exceptions::NotFoundException Rzucany, gdy parametr o wskazanej nazwie nie mo¿e zostaæ znaleziony.
			 */
			const std::wstring& GetParameter(const std::wstring& name) const
			{
				auto it = this->Parameters->find(name);
				if (it == this->Parameters->end())
					throw Exceptions::NotFoundException();
				return it->second;
			}

		private:
			ParametersPointer Parameters;
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