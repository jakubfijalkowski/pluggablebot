#pragma once
#include <string>
#include <memory>
#include <map>
#include "../Exceptions/NotFoundException.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Wynik parsowania wiadomo�ci, zwracany przez IParser. Zawiera nazw� oraz wszystkie parametry, kt�re uda�o si� dopasowa�.
		 */
		class ParseResults
		{
		public:
			/**
			 * Typ listy parametr�w(w�a�ciwej).
			 */
			typedef std::map<std::string, std::string> ParameterList;

			/**
			 * Typ u�ywany do przechowywania i przekazywania listy parametr�w.
			 */
			typedef std::unique_ptr<ParameterList> ParametersPointer;

			/**
			 * Nazw� komendy, nawet je�li by�a to komenda pe�no tekstowa i nie uda�o si�
			 * jej inaczej zinterpretowa�(jest to fragment do pierwszego bia�ego znaku).
			 */
			const std::string Name;

			/**
			 * Okre�la, czy uda�o si� dopasowa� tekst do formatu komendy zwyk�ej.
			 * Je�li jest fa�szem, oznacza to, �e komenda powinna by� tylko rozwa�ana
			 * jako pe�no tekstowa.
			 */
			const bool IsSuccess;

			/**
			 * Inicjalizuje obiekt, kt�ry okre�la wynik parsowania komendy
			 * pe�no tekstowej(IsSuccess b�dzie ustawiony na false).
			 */
			ParseResults(const std::string& name)
				: Name(name), IsSuccess(false)
			{ }

			/**
			 * Inicjalizuje obiekt, kt�ry okre�la wynik parsowania zwyk�ej komendy.
			 */
			ParseResults(const std::string& name, ParametersPointer parameters)
				: Name(name), IsSuccess(true), Parameters(std::move(parameters))
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
			bool HasParameter(const std::string& name) const
			{
				return this->Parameters->find(name) != this->Parameters->end();
			}

			/**
			 * Pobiera warto�� parametru o wskazanej nazwie. Je�li nie istnieje, metoda rzuca wyj�tek.
			 *
			 * \param name Nazwa parametru.
			 * \exception Exceptions::NotFoundException Rzucany, gdy parametr o wskazanej nazwie nie mo�e zosta� znaleziony.
			 */
			const std::string& GetParameter(const std::string& name) const
			{
				auto it = this->Parameters->find(name);
				if (it == this->Parameters->end())
					throw Exceptions::NotFoundException();
				return it->second;
			}

		private:
			ParametersPointer Parameters;
		};

		typedef std::shared_ptr<const ParseResults> ParseResultsPointer;

	}
}