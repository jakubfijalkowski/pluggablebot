#include "IMatcher.h"

namespace PluggableBot
{
	namespace Commands
	{
		bool SimpleMatcher::Matches(const ExecutionContext& context) const
		{
			if (!context.ParseResults->IsSuccess || context.ParseResults->Name != this->name)
			{
				return false;
			}
			for (auto p : this->parameters)
			{
				if (!context.ParseResults->HasParameter(p))
				{
					return false;
				}
			}

			return true;
		}

		bool RegexMatcher::Matches(const ExecutionContext& context) const
		{
			return std::regex_match(context.Message->Content, this->expression);
		}
	}
}
