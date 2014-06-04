#pragma once
#include <string>
#include <regex>
#include "../Config.h"
#include "ExecutionContext.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * \brief Klasy implementujące ten interfejs są odpowiedzialne za dopasowywanie tekstu do komend.
		 *
		 * Są odpowiedzialne tylko za określenie, czy komenda jest, czy nie, pełno tekstowa
		 * oraz stwierdzenie, czy komenda pasuje do wyników parsowania.
		 */
		class PLUGIN_API IMatcher
		{
		public:
			/**
			 * \brief Określa, czy komenda jest pełno tekstowa, czy nie.
			 */
			const bool IsFullText;

			/**
			 * \brief Próbuje dopasować wynik parsowania do komendy.
			 * 
			 * Jeśli komenda jest pełno tekstowa(IsFullText zwraca true), implementacje tej metody
			 * powinny pracować na ExecutionContext::Message::FullText, jeśli nie - na pozostałych
			 * parametrach.
			 */
			virtual bool Matches(const ExecutionContext& context) const = 0;

			/**
			 * \brief Deinicjalizuje obiekt.
			 */
			virtual ~IMatcher() { }

		protected:
			/**
			 * \brief Inicjalizuje obiekt.
			 */
			IMatcher(bool isFullText = false)
				: IsFullText(isFullText)
			{ }
		};

		/**
		 * \brief Najprostsza z implementacji IMatcher. Wiadomość pasuje, gdy zgadza się nazwa
		 * oraz są obecne wszystkie parametry.
		 */
		class PLUGIN_API SimpleMatcher
			: public IMatcher
		{
		public:
			/**
			 * \brief Inicjalizuje obiekt niezbędnymi informacjami
			 */
			SimpleMatcher(const std::string& name, std::initializer_list<std::string> params)
				: IMatcher(false), name(name), parameters(params)
			{ }

			/**
			 * \brief Próbuje dopasować tekst wiadomości do określonego wzorca.
			 */
			virtual bool Matches(const ExecutionContext& context) const;

		private:
			std::string name;
			std::vector<std::string> parameters;
		};

		/**
		 * \brief IMatcher używający wyrażeń regularnych. Wiadomość pasuje, gdy wyrażenie
		 * regularne pasuje do niej.
		 */
		class PLUGIN_API RegexMatcher
			: public IMatcher
		{
		public:
			/**
			 * \brief Wyrażenie używane przez obiekt.
			 */
			const std::regex Expression;

			/**
			 * \brief Inicjalizuje wyrażenie regularne.
			 */
			RegexMatcher(const std::string& regexString)
				: IMatcher(true), Expression(regexString)
			{ }


			/**
			* \brief Próbuje dopasować tekst wiadomości do określonego wzorca.
			*/
			virtual bool Matches(const ExecutionContext& context) const;
		};
	}
}
