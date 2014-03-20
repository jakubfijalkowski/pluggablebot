#pragma once
#include <string>
#include <memory>
#include <map>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		* Wynik parsowania tekstu, zwracany przez parser. Zawiera nazw� oraz wszystkie parametry, kt�re uda�o si� dopasowa�.
		*/
		class CommandParseResults
		{
		public:
			/**
			 * Typ listy parametr�w(w�a�ciwej).
			 */
			typedef std::map<std::wstring, std::wstring> ParameterList;

			/**
			 * Typ u�ywany do przechowywania i przekazywania listy parametr�w.
			 */
			typedef std::shared_ptr<ParameterList> ParametersPointer;

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
			* Inicjalizuje obiekt, kt�ry okre�la wynik parsowania zwyk�ej komendy.
			*/
			CommandParseResults(const std::wstring& name, const std::wstring& fullText, ParametersPointer parameters)
				: Name(name), FullText(fullText), IsSuccess(true), Parameters(parameters)
			{ }

			/**
			* Pobiera ilo�� parametr�w, o ile parsowanie si� uda�o.
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
			 * Pobiera warto�� parametru o wskazanej nazwie. Je�li nie istnieje, metoda rzuca wyj�tek.
			 *
			 * \param name Nazwa parametru.
			 * \exception Exceptions::NotFoundException Rzucany, gdy parametr o wskazanej nazwie nie mo�e zosta� znaleziony.
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