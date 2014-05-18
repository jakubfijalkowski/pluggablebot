#include "StatelessPlugin.h"

#include "HelpCommand.h"
#include "StopCommand.h"

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