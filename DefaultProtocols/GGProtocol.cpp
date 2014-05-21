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
			: IProtocol("Gadu-Gadu"), Logger(Logging::LogFactory::GetLogger("GGProtocol")), context(context)
		{ }

		GGProtocol::~GGProtocol()
		{ }

		ConfigurationStatus GGProtocol::CheckConfiguration(const jsonxx::Object& config)
		{
			if (config.get<jsonxx::Boolean>("disable", false))
			{
				return ConfigurationStatus::Disabled;
			}
			if (!config.has<jsonxx::Number>("number") || !config.has<std::string>("password"))
			{
				return ConfigurationStatus::Invalid;
			}
			return ConfigurationStatus::Valid;
		}

		void GGProtocol::Start()
		{
			WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			{
				Logger->Fatal("Cannot initialize WinSock.");
				throw std::system_error(std::error_code(WSAGetLastError(), std::generic_category()), "Cannot initialize WinSock.");
			}

		}

		void GGProtocol::Stop()
		{
			WSACleanup();
		}

	}
}