#include "StatelessPlugin.h"

namespace PluggableBot
{
	namespace StatelessCommands
	{

		StatelessPlugin::StatelessPlugin(ApplicationContext* context)
			: name("StatelessPlugin"), context(context)
		{ }

		const std::string& StatelessPlugin::GetName() const
		{
			return this->name;
		}

		void StatelessPlugin::Configure(const jsonxx::Object& configuration)
		{ }

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