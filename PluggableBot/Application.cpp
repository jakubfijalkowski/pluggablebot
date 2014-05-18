#include <fstream>
#include <thread>
#include "Application.h"
#include "Commands/IParser.h"
#include "Commands/ICommandExecutor.h"
#include "Plugins/PluginManager.h"
#include "External/jsonxx.h"

namespace PluggableBot
{

	static const char* ConfigPath = "pluggablebot.config";

	void Application::Initialize()
	{
		Logger = Logging::LogFactory::GetLogger("Application");

		Logger->Debug("Initializing.");

		std::ifstream configFile(ConfigPath);
		if (configFile)
		{
			Logger->Debug("Config file found. Parsing.");
			this->configuration.parse(configFile);
		}
		else
		{
			Logger->Warning("Cannot find config file. Using default.");
		}

		auto messenger = new Messaging::Messenger();
		auto parser = new Commands::DefaultParser();
		auto executor = new Commands::DefaultCommandExecutor(parser);

		this->context.reset(new ApplicationContext(messenger, executor));

		this->context->Set(new Plugins::PluginManager(this->context.get()));

		Logger->Information("All subsystems created. Initializing subsystems.");
		this->context->GetPlugins()->Configure(this->configuration);
		this->context->GetPlugins()->Load();

		Logger->Information("All subsystems initialized. Returning control to main thread.");
	}

	int Application::Run()
	{
		std::thread([&](){
			while (!this->exiting)
			{
				Sleep(1000);
			}
		}).join();
		return 0;
	}

	void Application::Shutdown()
	{
		this->exiting = true;
	}

	void Application::Deinitialize()
	{
		Logger->Debug("Deinitializing.");

		this->context->GetPlugins()->Unload();

		delete this->context->GetPlugins();
		delete this->context->CommandExecutor;
		delete this->context->Messenger;
		this->context.reset(nullptr);

		Logger->Information("Application context destroyed. Exiting.");
	}

}