#include "StatelessPlugin.h"

#include "HelpCommand.h"
#include "StopCommand.h"
#include "PingCommand.h"
#include "SendCommand.h"
#include "ListProtocolsCommand.h"

namespace PluggableBot
{
	namespace StatelessCommands
	{

		StatelessPlugin::StatelessPlugin(ApplicationContext* context)
			: name("StatelessPlugin"), context(context)
		{ }

		StatelessPlugin::~StatelessPlugin()
		{
			for (auto p : this->supportedCommands)
			{
				delete p;
			}
			this->supportedCommands.clear();
		}

		const std::string& StatelessPlugin::GetName() const
		{
			return this->name;
		}

		void StatelessPlugin::Configure(const jsonxx::Object& configuration)
		{
			this->supportedCommands.push_back(new HelpCommand(this->context));
			this->supportedCommands.push_back(new StopCommand(this->context));
			this->supportedCommands.push_back(new PingCommand(this->context));
			this->supportedCommands.push_back(new SendCommand(this->context));
			this->supportedCommands.push_back(new ListProtocolsCommand(this->context));
		}

		const IPlugin::CommandList* StatelessPlugin::GetSupportedCommands() const
		{
			return &this->supportedCommands;
		}

		const IPlugin::ProtocolList* StatelessPlugin::GetSupportedProtocols() const
		{
			return nullptr;
		}


		extern "C"
		{
			IPlugin* CreatePlugin(ApplicationContext* context)
			{
				return new StatelessPlugin(context);
			}

			void DeletePlugin(IPlugin* plugin)
			{
				delete (StatelessPlugin*)plugin;
			}
		}

	}
}