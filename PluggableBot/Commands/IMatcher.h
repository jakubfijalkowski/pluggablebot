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
		 * Klasy implementujące ten interfejs są odpowiedzialne za dopasowywanie tekstu do komend.
		 * Są odpowiedzialne tylko za określenie, czy komenda jest, czy nie, pełno tekstowa
		 * oraz stwierdzenie, czy komenda pasuje.
		 */
		class PLUGIN_API IMatcher
		{
		public:
			/**
			 * Określa, czy komenda jest pełno tekstowa, czy nie.
			 */
			const bool IsFullText;

			/**
			 * Próbuje dopasować wynik parsowania do komendy.
			 * Jeśli komenda jest pełno tekstowa(IsFullText zwraca true), implementacje tej metody
			 * powinny pracować na ExecutionContext::Message::FullText, jeśli nie - na pozostałych parametrach.
			 */
			virtual bool Matches(const ExecutionContext& context) const = 0;

			virtual ~IMatcher() { }

		protected:
			/**
			 * Inicjalizuje obiekt.
			 */
			IMatcher(bool isFullText = false)
				: IsFullText(isFullText)
			{ }
		};

		/**
		 * Będzie pasować dla zwykłych komend, z określonymi parametrami.
		 */
		class PLUGIN_API SimpleMatcher
			: public IMatcher
		{
		public:
			SimpleMatcher(const std::string& name, std::initializer_list<std::string> params)
				: IMatcher(false), name(name), parameters(params)
			{ }

			virtual bool Matches(const ExecutionContext& context) const;

		private:
			std::string name;
			std::vector<std::string> parameters;
		};

		/**
		 * Będzie pasować dla komend spełniających podane wyrażenie regularne.
		 */
		class PLUGIN_API RegexMatcher
			: public IMatcher
		{
		public:
			/**
			 * Wyrażenie używane przez obiekt.
			 */
			const std::regex Expression;

			RegexMatcher(const std::string& regexString)
				: IMatcher(true), Expression(regexString)
			{ }

			virtual bool Matches(const ExecutionContext& context) const;
		};
	}
}
