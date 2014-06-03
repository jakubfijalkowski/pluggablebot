#include "FilesystemPlugin.h"

#include "PWDCommand.h"
#include "CDCommand.h"
#include "CatCommand.h"
#include "MvCommand.h"
#include "RmCommand.h"
#include "LsCommand.h"
#include "ExecuteCommand.h"
#include "StoreTextCommand.h"
#include "StoreImageCommand.h"

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
			this->supportedCommands.push_back(new CatCommand(this->context));
			this->supportedCommands.push_back(new MvCommand(this->context));
			this->supportedCommands.push_back(new RmCommand(this->context));
			this->supportedCommands.push_back(new LsCommand(this->context));
			this->supportedCommands.push_back(new ExecuteCommand(this->context));
			this->supportedCommands.push_back(new StoreTextCommand(this->context));
			this->supportedCommands.push_back(new StoreImageCommand(this->context));
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