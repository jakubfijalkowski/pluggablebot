#include "DefaultProtocolsPlugin.h"
#include "GGProtocol.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		DefaultProtocolsPlugin::DefaultProtocolsPlugin(ApplicationContext* context)
			: name("DefaultProtocols"), Logger(Logging::LogFactory::GetLogger("DefaultProtocols")), context(context)
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
				auto config = configuration.get<jsonxx::Object>("gg");
				auto status = GGProtocol::CheckConfiguration(config);
				if (status == ConfigurationStatus::Valid)
				{
					auto gg = new GGProtocol(this->context, config);
					this->suppotedProtocols.push_back(gg);
				}
				else if (status == ConfigurationStatus::Disabled)
				{
					Logger->Information("Gadu-Gadu support is disabled.");
				}
				else
				{
					Logger->Warning("Gadu-Gadu configuration is invalid.");
				}
			}
			else
			{
				Logger->Warning("There is no configuration entry for Gadu-Gadu.");
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