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
		 * Wynik parsowania wiadomoœci, zwracany przez IParser. Zawiera nazwê oraz wszystkie parametry, które uda³o siê dopasowaæ.
		 */
		class ParseResults
		{
		public:
			/**
			 * Typ listy parametrów(w³aœciwej).
			 */
			typedef std::map<std::string, std::string> ParameterList;

			/**
			 * Typ u¿ywany do przechowywania i przekazywania listy parametrów.
			 */
			typedef std::unique_ptr<ParameterList> ParametersPointer;

			/**
			 * Nazwê komendy, nawet jeœli by³a to komenda pe³no tekstowa i nie uda³o siê
			 * jej inaczej zinterpretowaæ(jest to fragment do pierwszego bia³ego znaku).
			 */
			const std::string Name;

			/**
			 * Okreœla, czy uda³o siê dopasowaæ tekst do formatu komendy zwyk³ej.
			 * Jeœli jest fa³szem, oznacza to, ¿e komenda powinna byæ tylko rozwa¿ana
			 * jako pe³no tekstowa.
			 */
			const bool IsSuccess;

			/**
			 * Inicjalizuje obiekt, który okreœla wynik parsowania komendy
			 * pe³no tekstowej(IsSuccess bêdzie ustawiony na false).
			 */
			ParseResults(const std::string& name)
				: Name(name), IsSuccess(false)
			{ }

			/**
			 * Inicjalizuje obiekt, który okreœla wynik parsowania zwyk³ej komendy.
			 */
			ParseResults(const std::string& name, ParametersPointer parameters)
				: Name(name), IsSuccess(true), Parameters(std::move(parameters))
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
			bool HasParameter(const std::string& name) const
			{
				return this->Parameters->find(name) != this->Parameters->end();
			}

			/**
			 * Pobiera wartoœæ parametru o wskazanej nazwie. Jeœli nie istnieje, metoda rzuca wyj¹tek.
			 *
			 * \param name Nazwa parametru.
			 * \exception Exceptions::NotFoundException Rzucany, gdy parametr o wskazanej nazwie nie mo¿e zostaæ znaleziony.
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