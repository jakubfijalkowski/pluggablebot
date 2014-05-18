#include "DefaultProtocolsPlugin.h"
#include "GGProtocol.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		DefaultProtocolsPlugin::DefaultProtocolsPlugin(ApplicationContext* context)
			: name("DefaultProtocols"), context(context)
		{ }

		DefaultProtocolsPlugin::~DefaultProtocolsPlugin()
		{
			for (auto p : this->suppotedProtocols)
			{
				delete p;
			}
			this->suppotedProtocols.clear();
		}

		const std::string& DefaultProtocolsPlugin::GetName() const
		{
			return this->name;
		}

		void DefaultProtocolsPlugin::Configure(const jsonxx::Object& configuration)
		{
			if (configuration.has<jsonxx::Object>("gg"))
			{
				this->suppotedProtocols.push_back(
					new GGProtocol(
					this->context,
					configuration.get<jsonxx::Object>("gg")
					));
			}
		}

		const IPlugin::CommandList* DefaultProtocolsPlugin::GetSupportedCommands() const
		{
			return nullptr;
		}

		const IPlugin::ProtocolList* DefaultProtocolsPlugin::GetSupportedProtocols() const
		{
			return &this->suppotedProtocols;
		}

		extern "C"
		{
			IPlugin* CreatePlugin(ApplicationContext* context)
			{
				return new DefaultProtocolsPlugin(context);
			}

			void DeletePlugin(IPlugin* plugin)
			{
				delete (DefaultProtocolsPlugin*)plugin;
			}
		}

	}
}