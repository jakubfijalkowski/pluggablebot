#include <PluggableBot/Messages/Messages.h>
#include <thread>
#include <Windows.h>
#include "GGProtocol.h"
#include "ConnectionFailureException.h"

#undef SendMessage

namespace PluggableBot
{
	namespace DefaultProtocols
	{
		using namespace Messaging;

		const int EventWaitTime = 100;
		const int DefaultMaxRetryCount = 10;

		GGProtocol::GGProtocol(ApplicationContext* context, const jsonxx::Object& config)
			: IProtocol("Gadu-Gadu"), Logger(Logging::LogFactory::GetLogger("GGProtocol")), context(context),
			MaxRetryCount((int)config.get<jsonxx::Number>("max_retry_count", DefaultMaxRetryCount)),
			shouldShutdown(false)
		{
			int uid = (int)config.get<jsonxx::Number>("number");
			const std::string& password = config.get<std::string>("password");
			int status = (int)config.get<jsonxx::Number>("status", GG_STATUS_AVAIL);
			const std::string& statusDesc = config.get<std::string>("status_description", "");

			if (config.has<jsonxx::Array>("contacts"))
			{
				auto& arr = config.get<jsonxx::Array>("contacts");
				// Ignoruje wartoœci nie bêd¹ce liczbami
				for (auto& n : arr.values())
				{
					if (n->is<jsonxx::Number>())
					{
						this->contacts.push_back(n->get<jsonxx::Number>());
					}
				}
			}

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

			this->shouldShutdown = false;
			this->main = std::thread([&]()
			{
				int retryCount = 0;
				this->ThreadMain(retryCount);
			});
		}

		void GGProtocol::Stop()
		{
			Logger->Information("Disconnecting.");
			this->shouldShutdown = true;
			this->main.join();
			WSACleanup();
		}

		void GGProtocol::ThreadMain(int& retryCount)
		{
			while (retryCount <= this->MaxRetryCount && !this->TryConnect())
			{
				Logger->Warning("Cannot connect to the server. Retrying.");
				retryCount++;
			}

			if (retryCount > this->MaxRetryCount)
			{
				Logger->Fatal("MaxRetryCount reached. Protocol failed.");
				auto msg = new Messages::ProtocolFailure(this);
				this->context->Messenger->Send(Messaging::MessagePointer(msg));
				return;
			}

			Logger->Information("Connected.");
			while (!this->shouldShutdown)
			{
				if (!this->HandleGGEvents())
				{
					Logger->Error("Cannot handle server messages. Retrying.");
					this->ThreadMain(retryCount);
					return;
				}
				this->HandleSystemEvents();
			}
			this->client->Disconnect();
		}

		bool GGProtocol::TryConnect()
		{
			try
			{
				this->client->Connect(this->contacts);
			}
			catch (ConnectionFailureException ex)
			{
				Logger->Error("Cannot connect to Gadu-Gadu server. Error: {0}", ex.what());
				return false;
			}
			return true;
		}

		bool GGProtocol::HandleGGEvents()
		{
			GGEvent event;
			try
			{
				event = this->client->HandleEvents();
			}
			catch (ConnectionFailureException ex)
			{
				Logger->Error("Connection to the server lost. Error: {0}", ex.what());
				return false;
			}

			if (event != nullptr)
			{
				if (event->type == GG_EVENT_MSG && event->event.msg.sender != 0)
				{
					char uin[12];
					_itoa_s(event->event.msg.sender, uin, 10);

					UserMessagePointer userMessage(new UserMessage((char*)event->event.msg.message, uin, this));
					this->context->Messenger->Send(MessagePointer(new Messages::MessageReceived(userMessage)));
				}
			}

			return true;
		}

		void GGProtocol::HandleSystemEvents()
		{
			auto messages = this->context->Messenger->TryGet([&](Messaging::IMessage* message)
			{
				return $MessageIs(Messages::SendMessage) && ((Messages::SendMessage*)message)->Protocol == this;
			});

			for (auto message : *messages)
			{
				auto sendMessage = (Messages::SendMessage*)message.get();
				this->client->SendMessage(strtoul(sendMessage->Recipient.c_str(), nullptr, 10), sendMessage->Content);
			}
		}

	}
}