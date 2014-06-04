#pragma once
#include <string>
#include <memory>
#include <map>
#include "../Config.h"
#include "../Exceptions/NotFoundException.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * \brief Wynik parsowania wiadomości, zwracany przez IParser.
		 * Zawiera nazwę oraz wszystkie parametry, które udało się dopasować.
		 */
		class PLUGIN_API ParseResults
		{
		public:
			/**
			 * \brief Typ listy parametrów(właściwej).
			 */
			typedef std::map<std::string, std::string> ParameterList;

			/**
			 * \brief Typ używany do przechowywania i przekazywania listy parametrów.
			 */
			typedef std::unique_ptr<ParameterList> ParametersPointer;

			/**
			 * \brief Nazwę komendy, nawet jeśli była to komenda pełno tekstowa i nie udało się
			 * jej inaczej zinterpretować(jest to fragment do pierwszego białego znaku).
			 */
			const std::string Name;

			/**
			 * \brief Określa, czy udało się dopasować tekst do formatu komendy zwykłej.
			 * Jeśli jest fałszem, oznacza to, że komenda powinna być tylko rozważana
			 * jako pełno tekstowa.
			 */
			const bool IsSuccess;

			/**
			 * \brief Inicjalizuje obiekt, który określa wynik parsowania komendy
			 * pełno tekstowej(IsSuccess będzie ustawiony na false).
			 */
			ParseResults(const std::string& name)
				: Name(name), IsSuccess(false)
			{ }

			/**
			 * \brief Inicjalizuje obiekt, który określa wynik parsowania zwykłej komendy.
			 */
			ParseResults(const std::string& name, ParametersPointer parameters)
				: Name(name), IsSuccess(true), Parameters(std::move(parameters))
			{ }

			/**
			 * \brief Pobiera ilość parametrów, o ile parsowanie się udało.
			 */
			int GetParameterCount() const
			{
				return this->Parameters->size();
			}

			/**
			 * \brief Sprawdza, czy wynik zawiera parametr o wskazanej nazwie.
			 *
			 * \param name Nazwa parametru.
			 */
			bool HasParameter(const std::string& name) const
			{
				return this->Parameters->find(name) != this->Parameters->end();
			}

			/**
			 * \brief Pobiera wartość parametru o wskazanej nazwie. Jeśli nie istnieje, metoda
			 * rzuca wyjątek.
			 *
			 * \param name Nazwa parametru.
			 * \exception Exceptions::NotFoundException Rzucany, gdy parametr o wskazanej nazwie
			 *            nie może zostać znaleziony.
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

		/**
		 * \brief Wskaźnik na wynik parsowania.
		 */
		typedef std::shared_ptr<const ParseResults> ParseResultsPointer;

	}
}