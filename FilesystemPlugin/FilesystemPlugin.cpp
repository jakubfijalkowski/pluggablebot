#include "FilesystemPlugin.h"

#include "PWDCommand.h"
#include "CDCommand.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		FilesystemPlugin::FilesystemPlugin(ApplicationContext* context)
			: name("FilesystemPlugin"), context(context)
		{ }

		FilesystemPlugin::~FilesystemPlugin()
		{
			for (auto p : this->supportedCommands)
			{
				delete p;
			}
			this->supportedCommands.clear();
		}

		const std::string& FilesystemPlugin::GetName() const
		{
			return this->name;
		}

		void FilesystemPlugin::Configure(const jsonxx::Object& configuration)
		{
			this->supportedCommands.push_back(new PWDCommand(this->context));
			this->supportedCommands.push_back(new CDCommand(this->context));
		}

		const IPlugin::CommandList* FilesystemPlugin::GetSupportedCommands() const
		{
			return &this->supportedCommands;
		}

		const IPlugin::ProtocolList* FilesystemPlugin::GetSupportedProtocols() const
		{
			return nullptr;
		}


		extern "C"
		{
			IPlugin* CreatePlugin(ApplicationContext* context)
			{
				return new FilesystemPlugin(context);
			}

			void DeletePlugin(IPlugin* plugin)
			{
				delete (FilesystemPlugin*)plugin;
			}
		}

	}
}