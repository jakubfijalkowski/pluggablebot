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
			 * Zwraca nazw� parametru.
			 */
			const std::wstring& GetName() const
			{

			}

			/**
			 * Zwraca warto�� parametru.
			 */
			const std::wstring& GetValue() const
			{

			}
		};

		/**
		 * Wynik parsowania tekstu, zwracany przez parser. Zawiera nazw� oraz wszystkie parametry, kt�re uda�o si� dopasowa�.
		 */
		class CommandParseResults
		{
		public:
			/**
			 * Okre�la, czy uda�o si� dopasowa� tekst do formatu komendy zwyk�ej.
			 * Je�li jest fa�szem, oznacza to, �e komenda powinna by� tylko rozwa�ana
			 * jako pe�notekstowa.
			 */
			bool IsSuccess() const
			{

			}

			/**
			 * Pobiera pe�ny tekst, kt�ry by� u�yty do parsowania.
			 */
			const std::wstring& GetFullText() const
			{

			}

			/**
			 * Pobiera nazw� komendy, nawet je�li by�a to komenda pe�notekstowa i nie uda�o si�
			 * jej inaczej zinterpretowa�(jest to fragment do pierwszego znaku).
			 */
			const std::wstring& GetName() const
			{

			}

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

	}
}