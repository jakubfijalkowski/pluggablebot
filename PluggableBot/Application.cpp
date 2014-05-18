#include <fstream>
#include <thread>
#include <algorithm>
#include "Application.h"
#include "Commands/IParser.h"
#include "Commands/ICommandExecutor.h"
#include "Plugins/PluginManager.h"
#include "External/jsonxx.h"

namespace PluggableBot
{
	using namespace Commands;
	using namespace Messages;
	using namespace Messaging;
	using namespace Plugins;

	static const DWORD WaitTime = 1000;
	static const char* ConfigPath = "config.json";
	static const char* AsyncMessage = "Wiadomoœæ jest wywo³ywana asynchronicznie. OdpowiedŸ otrzymasz, gdy wywo³anie zostanie zakoñczone.";
	static const char* CommandDoesNotExist = "Wiadomoœæ nie mog³a zostaæ przetworzona. Komenda jej odpowiadaj¹ca nie istnieje.";
	static const char* ExecutionExceptionMessage = "Wiadomoœæ nie mog³a zostaæ przetworzona. Komenda zwróci³a b³¹d.";

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

		auto messenger = new Messenger();
		auto parser = new DefaultParser();
		auto executor = new DefaultCommandExecutor(parser);

		this->context.reset(new ApplicationContext(messenger, executor));

		this->context->Set(new PluginManager(this->context.get()));

		Logger->Information("All subsystems created. Configuring subsystems.");
		this->context->GetPlugins()->Configure(this->configuration);
		this->context->GetPlugins()->Load();

		auto commands = this->context->GetPlugins()->GetCombinedCommands();
		this->context->CommandExecutor->AddCommands(commands);
		Logger->Information("{0} commands will be available.", commands.size());

		Logger->Information("All subsystems initialized. Returning control to main thread.");
	}

	ApplicationExitCode Application::Run()
	{
		if (!this->StartProtocols())
		{
			return ApplicationExitCode::NoWorkingProtocols;
		}

		this->exiting = false;
		std::thread([&]()
		{
			while (!this->exiting)
			{
				this->GetMessages();
			}
		}).join();

		this->StopProtocols();

		return this->exitCode;
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

	bool Application::StartProtocols()
	{
		for (auto protocol : this->context->GetPlugins()->GetCombinedProtocols())
		{
			try
			{
				Logger->Debug("Starting protocol {0}.", protocol->Name);
				protocol->Start();
				this->workingProtocols.push_back(protocol);
			}
			catch (std::exception ex)
			{
				Logger->Error("Protocol {0} has thrown an exception. Message: {1}.", protocol->Name, ex.what());
			}
		}
		if (this->workingProtocols.empty())
		{
			Logger->Fatal("There are no working protocols.");
			return false;
		}

		Logger->Information("All protocols started.");
		return true;
	}

	void Application::StopProtocols()
	{
		for (auto protocol : this->context->GetPlugins()->GetCombinedProtocols())
		{
			protocol->Stop();
		}
		Logger->Information("All protocols stopped.");
		this->workingProtocols.clear();
	}

	void Application::GetMessages()
	{
		auto msgs = this->context->Messenger->Get([](IMessage* message) -> bool
		{
			return
				$MessageIs(MessageReceived) ||
				$MessageIs(ProtocolFailure) ||
				$MessageIs(ShutdownRequest);
		}, WaitTime);

		for (auto message : *msgs)
		{
			$HandleMessage(MessageReceived);
			$HandleMessage(ProtocolFailure);
			$HandleMessage(ShutdownRequest);
		}
	}

	void Application::Handle(MessageReceived* message)
	{
		Logger->Information("Message received from {0}. Trying to interpret it.", message->UserMessage->Sender);

		//TODO: add sending JSON
		std::string content;
		try
		{
			auto result = this->context->CommandExecutor->Execute(message->UserMessage);
			if (result.IsAsync)
			{
				content = AsyncMessage;
			}
			else
			{
				content = result.Message;
			}
		}
		catch (Exceptions::NotFoundException ex)
		{
			Logger->Debug("Cannot find command for the message.");
			content = CommandDoesNotExist;
		}
		catch (Exceptions::ExecutionException ex)
		{
			Logger->Debug("Cannot execute the command. Message: {0}, error code: {1}.", ex.what(), ex.ErrorCode);
			content = ExecutionExceptionMessage;
		}

		this->context->Messenger->Send(new SendMessage(content, message->UserMessage->Sender, message->UserMessage->SourceProtocol));
	}

	void Application::Handle(ProtocolFailure* message)
	{
		Logger->Error("Protocol {0} failed.", message->Protocol->Name);

		auto it = std::find(this->workingProtocols.begin(), this->workingProtocols.end(), message->Protocol);
		if (it == this->workingProtocols.end())
		{
			Logger->Fatal("Protocol {0} was not working at the time of the message. Possible cause: bug in the protocol plugin.");
			return;
		}

		this->workingProtocols.erase(it);
		if (this->workingProtocols.empty())
		{
			this->exitCode = ApplicationExitCode::ProtocolsFailed;
			this->exiting = true;
		}
	}

	void Application::Handle(ShutdownRequest* message)
	{
		Logger->Information("ShutdownRequest received. Stopping application.");
		this->exiting = true;
	}
}