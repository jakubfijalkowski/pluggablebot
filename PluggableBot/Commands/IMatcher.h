#pragma once
#include <string>
#include <regex>
#include "ExecutionContext.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Klasy implementuj¹ce ten interfejs s¹ odpowiedzialne za dopasowywanie tekstu do komend.
		 * S¹ odpowiedzialne tylko za okreœlenie, czy komenda jest, czy nie, pe³no tekstowa
		 * oraz stwierdzenie, czy komenda pasuje.
		 */
		class IMatcher
		{
		public:
			/**
			 * Okreœla, czy komenda jest pe³no tekstowa, czy nie.
			 */
			const bool IsFullText;

			/**
			 * Próbuje dopasowaæ wynik parsowania do komendy.
			 * Jeœli komenda jest pe³no tekstowa(IsFullText zwraca true), implementacje tej metody
			 * powinny pracowaæ na ExecutionContext::Message::FullText, jeœli nie - na pozosta³ych parametrach.
			 */
			virtual bool Matches(const ExecutionContext& context) = 0;

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
		 * Bêdzie pasowaæ dla zwyk³ych komend, z okreœlonymi parametrami.
		 */
		class SimpleMatcher
			: public IMatcher
		{
		public:
			SimpleMatcher(const std::string& name, std::initializer_list<std::string> params)
				: IMatcher(false), name(name), parameters(params)
			{ }

			virtual bool Matches(const ExecutionContext& context);

		private:
			std::string name;
			std::vector<std::string> parameters;
		};

		/**
		 * Bêdzie pasowaæ dla komend spe³niaj¹cych podane wyra¿enie regularne.
		 */
		class RegexMatcher
			: public IMatcher
		{
		public:
			RegexMatcher(const std::string& regexString)
				: IMatcher(true), expression(regexString)
			{ }

			virtual bool Matches(const ExecutionContext& context);

		private:
			std::regex expression;
		};
	}
}
