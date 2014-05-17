#pragma once
#include "LogFactory.h"

namespace PluggableBot
{
	namespace Logging
	{
		std::vector<IOutput*> LogFactory::outputs;

		LoggerPointer LogFactory::GetLogger(const std::string& name)
		{
			return LoggerPointer(new Logger(name, outputs));
		}

		void LogFactory::AddOutput(IOutput* output)
		{
			outputs.push_back(output);
		}

		void LogFactory::Unload()
		{
			for (auto out : outputs)
			{
				delete out;
			}
			outputs.clear();
		}
	}
}