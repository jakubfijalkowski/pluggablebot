#include <PluggableBot/Messages/MessageReceived.h>
#include <thread>
#include <Windows.h>
#include "GGProtocol.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{
		using namespace Messaging;

		GGProtocol::GGProtocol(ApplicationContext* context)
			: IProtocol("Gadu-Gadu"), context(context)
		{ }

		GGProtocol::~GGProtocol()
		{ }

		bool GGProtocol::Configure(const jsonxx::Object& config)
		{
			return false;
		}

		void GGProtocol::Start()
		{
			this->main = std::thread([&]()
			{
				Sleep(1000);
				UserMessagePointer userMsg(new UserMessage("stop", "gg:123", this));
				this->context->Messenger->Send(MessagePointer(new Messages::MessageReceived(userMsg)));
			});
		}

		void GGProtocol::Stop()
		{
			this->main.join();
		}

	}
}