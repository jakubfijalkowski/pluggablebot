#include <PluggableBot/Messages/Messages.h>
#include <thread>
#include <Windows.h>
#include "GGProtocol.h"
#include "ConnectionFailureException.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{
		using namespace Messaging;

		const int EventWaitTime = 1;
		const int DefaultMaxRetryCount = 10;

		GGProtocol::GGProtocol(ApplicationContext* context, const jsonxx::Object& config)
			: IProtocol("Gadu-Gadu"), Logger(Logging::LogFactory::GetLogger("GGProtocol")), context(context),
			MaxRetryCount((int)config.get<jsonxx::Number>("max_retry_count", DefaultMaxRetryCount))
		{
			int uid = (int)config.get<jsonxx::Number>("number");
			const std::string& password = config.get<std::string>("password");
			int status = (int)config.get<jsonxx::Number>("status", GG_STATUS_AVAIL);
			const std::string& statusDesc = config.get<std::string>("status_description", "");

			this->client.reset(new GGClient(uid, password, status, statusDesc, EventWaitTime));
		}

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

			this->main = std::thread([&]()
			{
				int retryCount = 0;
				while (!this->TryConnect())
				{
					Logger->Warning("Cannot connect to the server. Retrying.");
					retryCount++;
					if (retryCount > this->MaxRetryCount)
					{
						Logger->Fatal("MaxRetryCount reached. Protocol failed.");
						auto msg = new Messages::ProtocolFailure(this);
						this->context->Messenger->Send(Messaging::MessagePointer(msg));
						return;
					}
				}
				Logger->Information("Connected.");

			});
		}

		void GGProtocol::Stop()
		{
			Logger->Information("Disconnecting.");
			this->client->Disconnect();
			WSACleanup();
			this->main.join();
		}

		bool GGProtocol::TryConnect()
		{
			try
			{
				this->client->Connect();
			}
			catch (ConnectionFailureException ex)
			{
				Logger->Error("Cannot connect to Gadu-Gadu server. Error: {0}", ex.what());
				return false;
			}
			return true;
		}

	}
}