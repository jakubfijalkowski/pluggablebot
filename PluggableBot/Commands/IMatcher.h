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
		 * Klasy implementuj�ce ten interfejs s� odpowiedzialne za dopasowywanie tekstu do komend.
		 * S� odpowiedzialne tylko za okre�lenie, czy komenda jest, czy nie, pe�no tekstowa
		 * oraz stwierdzenie, czy komenda pasuje.
		 */
		class PLUGIN_API IMatcher
		{
		public:
			/**
			 * Okre�la, czy komenda jest pe�no tekstowa, czy nie.
			 */
			const bool IsFullText;

			/**
			 * Pr�buje dopasowa� wynik parsowania do komendy.
			 * Je�li komenda jest pe�no tekstowa(IsFullText zwraca true), implementacje tej metody
			 * powinny pracowa� na ExecutionContext::Message::FullText, je�li nie - na pozosta�ych parametrach.
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
		 * B�dzie pasowa� dla zwyk�ych komend, z okre�lonymi parametrami.
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
		 * B�dzie pasowa� dla komend spe�niaj�cych podane wyra�enie regularne.
		 */
		class PLUGIN_API RegexMatcher
			: public IMatcher
		{
		public:
			RegexMatcher(const std::string& regexString)
				: IMatcher(true), expression(regexString)
			{ }

			virtual bool Matches(const ExecutionContext& context) const;

		private:
			std::regex expression;
		};
	}
}
