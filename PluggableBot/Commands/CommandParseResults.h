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
			 * Zwraca nazwê parametru.
			 */
			const std::wstring& GetName() const
			{

			}

			/**
			 * Zwraca wartoœæ parametru.
			 */
			const std::wstring& GetValue() const
			{

			}
		};

		/**
		 * Wynik parsowania tekstu, zwracany przez parser. Zawiera nazwê oraz wszystkie parametry, które uda³o siê dopasowaæ.
		 */
		class CommandParseResults
		{
		public:
			/**
			 * Okreœla, czy uda³o siê dopasowaæ tekst do formatu komendy zwyk³ej.
			 * Jeœli jest fa³szem, oznacza to, ¿e komenda powinna byæ tylko rozwa¿ana
			 * jako pe³notekstowa.
			 */
			bool IsSuccess() const
			{

			}

			/**
			 * Pobiera pe³ny tekst, który by³ u¿yty do parsowania.
			 */
			const std::wstring& GetFullText() const
			{

			}

			/**
			 * Pobiera nazwê komendy, nawet jeœli by³a to komenda pe³notekstowa i nie uda³o siê
			 * jej inaczej zinterpretowaæ(jest to fragment do pierwszego znaku).
			 */
			const std::wstring& GetName() const
			{

			}

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

	}
}