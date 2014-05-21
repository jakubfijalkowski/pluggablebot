#include <PluggableBot/Messages/MessageReceived.h>
#include <thread>
#include <Windows.h>
#include "GGProtocol.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{
		using namespace Messaging;

		GGProtocol::GGProtocol(ApplicationContext* context, const jsonxx::Object& config)
			: IProtocol("Gadu-Gadu"), context(context)
		{ }

		GGProtocol::~GGProtocol()
		{ }

		ConfigurationStatus GGProtocol::CheckConfiguration(const jsonxx::Object& config)
		{
			return ConfigurationStatus::Valid;
		}

		void GGProtocol::Start()
		{
			this->main = std::thread([&]()
			{
			});
		}

		void GGProtocol::Stop()
		{
			this->main.join();
		}

	}
}