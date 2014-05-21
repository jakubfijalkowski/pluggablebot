#include <cctype>
#include "IParser.h"

namespace PluggableBot
{
	namespace Commands
	{

		void SkipWhiteSpace(const std::string& text, size_t& i)
		{
			while (i < text.length() && isspace(text[i]))
			{
				++i;
			}
		}

		void MoveToWhiteSpace(const std::string& text, size_t& i)
		{
			while (i < text.length() && !isspace(text[i]))
			{
				++i;
			}
		}

		void MoveToWitespaceOrChar(const std::string& text, size_t& i, char c)
		{
			while (i < text.length() && text[i] != c && !isspace(text[i]))
			{
				++i;
			}
		}

		void MoveToUnescapedChar(const std::string& text, size_t& i, char c)
		{
			while (i < text.length() && text[i] != c && (i == 0 || text[i - 1] != '\\'))
			{
				++i;
			}
		}

		bool ExtractPart(const std::string& text, size_t& i, std::string& part, char c)
		{
			size_t start, end;
			if (text[i] == '"')
			{
				start = i + 1;
				++i;
				MoveToUnescapedChar(text, i, '"');
				if (i == text.length())
				{
					return false;
				}
				end = i;
				++i;
			}
			else
			{
				start = i;
				MoveToWitespaceOrChar(text, i, c);
				end = i;
			}

			if (start == end)
			{
				return false;
			}

			part = text.substr(start, end - start);
			return true;
		}

		bool ExtractParameter(const std::string& text, size_t& i, ParseResults::ParameterList* parameters)
		{
			std::string name, value;
			if (!ExtractPart(text, i, name, '='))
			{
				return false;
			}

			SkipWhiteSpace(text, i);

			if (i == text.length() || text[i] != '=')
			{
				return false;
			}

			++i;
			SkipWhiteSpace(text, i);
			if (i == text.length())
			{
				return false;
			}

			if (!ExtractPart(text, i, value, '\0'))
			{
				return false;
			}
			parameters->emplace(name, value);
			return true;
		}

		ParseResultsPointer DefaultParser::Parse(const std::string& text)
		{
			std::string name;

			std::string lastParamName;

			size_t i = 0;

			// Wyłuskanie nazwy
			SkipWhiteSpace(text, i);
			if (!ExtractPart(text, i, name, '\0'))
			{
				return ParseResultsPointer(new ParseResults(text));
			}

			ParseResults::ParameterList* parameters = new ParseResults::ParameterList();
			SkipWhiteSpace(text, i);
			while (i < text.length())
			{
				if (!ExtractParameter(text, i, parameters))
				{
					return ParseResultsPointer(new ParseResults(text));
				}
				SkipWhiteSpace(text, i);
			}
			return ParseResultsPointer(new ParseResults(name, ParseResults::ParametersPointer(parameters)));
		}

	}
}