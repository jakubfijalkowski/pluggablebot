#pragma once
#include "IOutput.h"
#include "format.h"

namespace PluggableBot
{
	namespace Logging
	{

		Logger::Logger(const std::string& name, const std::vector<IOutput*>& outputs)
			: name(name), outputs(outputs)
		{ }

		void Logger::Log(LogLevel level, const std::string& message)
		{
			for (auto output : outputs)
			{
				output->Write(level, this->name, message);
			}
		}

	}
}