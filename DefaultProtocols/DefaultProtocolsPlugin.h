#pragma once
#include <PluggableBot/Plugins/IPlugin.h>

namespace PluggableBot
{
	namespace DefaultProtocols
	{
		using namespace PluggableBot::Plugins;

		/**
		 * Plugin z obs³ug¹ podstawowych protoko³ów.
		 */
		class DefaultProtocolsPlugin
			: public IPlugin
		{
		public:
			DefaultProtocolsPlugin(ApplicationContext* context);
			virtual ~DefaultProtocolsPlugin();

			virtual const std::string& GetName() const;
			virtual void Configure(const jsonxx::Object& configuration);
			virtual const CommandList* GetSupportedCommands() const;
			virtual const ProtocolList* GetSupportedProtocols() const;

		private:
			std::string name;
			ProtocolList suppotedProtocols;

			ApplicationContext* context;
		};

		extern "C"
		{
			__declspec(dllexport) IPlugin* CreatePlugin(ApplicationContext* context);
			__declspec(dllexport) void DeletePlugin(IPlugin* plugin);
		}
	}
}