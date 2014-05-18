#pragma once
#include <PluggableBot/Plugins/IPlugin.h>

namespace PluggableBot
{
	namespace StatelessCommands
	{
		using namespace PluggableBot::Plugins;

		/**
		 * Plugin z podstawowymi, bezstanowymi komendami.
		 */
		class StatelessPlugin
			: public IPlugin
		{
		public:
			StatelessPlugin(ApplicationContext* context);
			virtual const std::string& GetName() const;
			virtual void Configure(const jsonxx::Object& configuration);
			virtual const CommandList* GetSupportedCommands() const;
			virtual const ProtocolList* GetSupportedProtocols() const;

		private:
			std::string name;
			CommandList supportedCommands;

			ApplicationContext* context;
		};

		extern "C"
		{
			__declspec(dllexport) IPlugin* CreatePlugin(ApplicationContext* context);
			__declspec(dllexport) void DeletePlugin(IPlugin* plugin);
		}
	}
}