#include <fstream>
#include <thread>
#include <algorithm>
#include "Application.h"
#include "Other.h"
#include "Commands/IParser.h"
#include "Commands/ICommandExecutor.h"
#include "Plugins/PluginManager.h"
#include "External/jsonxx.h"
#include "External/format.h"

namespace PluggableBot
{
	using namespace Commands;
	using namespace Messages;
	using namespace Messaging;
	using namespace Plugins;

	static const DWORD WaitTime = 100;
	static const std::string ConfigPath = "config.json";
	static const std::string AsyncMessage = "Wiadomość jest wywoływana asynchronicznie. Odpowiedź otrzymasz, gdy wywołanie zostanie zakończone.";
	static const std::string CommandDoesNotExist = "Wiadomość nie mogła zostać przetworzona. Komenda jej odpowiadająca nie istnieje.";
	static const std::string ExecutionExceptionMessage = "Wiadomość nie mogła zostać przetworzona. Komenda zwróciła błąd: {0}.";
	static const std::string ExecutionExceptionWithSystemErrorMessage = "Wiadomość nie mogła zostać przetworzona. Komenda zwróciła błąd: {0}.\nWystąpił błąd systemowy {1}: {2}";

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

		this->sendJSON = this->configuration.get<jsonxx::Boolean>("sendJSON", false);

		auto messenger = new Messenger();
		auto parser = new DefaultParser();
		auto executor = new DefaultCommandExecutor(parser);

		this->context.reset(new ApplicationContext(messenger, executor, (ProtocolList*)&this->protocols));

		this->context->Set(new PluginManager(this->context.get()));

		Logger->Information("All subsystems created. Configuring subsystems.");
		this->context->GetPlugins()->Configure(this->configuration);
		this->context->GetPlugins()->Load();

		auto commands = this->context->GetPlugins()->GetCombinedCommands();
		this->context->CommandExecutor->AddCommands(commands);
		Logger->Information("{0} commands will be available.", commands.size());

		for (auto protocol : this->context->GetPlugins()->GetCombinedProtocols())
		{
			this->protocols.push_back(ProtocolState(protocol));
		}
		Logger->Information("{0} protocols should be available.", this->protocols.size());

		Logger->Information("All subsystems initialized. Returning control to main thread.");
	}

	ApplicationExitCode Application::Run()
	{
		if (!this->StartProtocols())
		{
			return ApplicationExitCode::NoWorkingProtocols;
		}

		this->exiting = false;
		while (!this->exiting)
		{
			this->GetMessages();
		}
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


		delete this->context->CommandExecutor;
		delete this->context->Messenger;

		this->context->GetPlugins()->Unload();
		delete this->context->GetPlugins();
		this->context.reset(nullptr);

		Logger->Information("Application context destroyed. Exiting.");
	}

	bool Application::HasWorkingProtocol()
	{
		for (auto& p : this->protocols)
		{
			if (p.IsWorking)
			{
				return true;
			}
		}
		return false;
	}

	bool Application::StartProtocols()
	{
		for (auto& protocol : this->protocols)
		{
			try
			{
				Logger->Debug("Starting protocol {0}.", protocol.Protocol->Name);
				protocol.Protocol->Start();
				protocol.IsWorking = true;
			}
			catch (std::exception ex)
			{
				Logger->Error("Protocol {0} has thrown an exception. Message: {1}.", protocol.Protocol->Name, ex.what());
				protocol.IsWorking = false;
			}
		}
		if (!this->HasWorkingProtocol())
		{
			Logger->Fatal("There are no working protocols.");
			return false;
		}

		Logger->Information("All protocols started.");
		return true;
	}

	void Application::StopProtocols()
	{
		for (auto& protocol : this->protocols)
		{
			protocol.Protocol->Stop();
			protocol.IsWorking = false;
		}
		Logger->Information("All protocols stopped.");
	}

	void Application::GetMessages()
	{
		auto msgs = this->context->Messenger->Get([](IMessage* message) -> bool
		{
			return
				$MessageIs(MessageReceived) ||
				$MessageIs(ProtocolFailure) ||
				$MessageIs(ShutdownRequest) ||
				$MessageIs(AsyncExecutionFailure) ||
				$MessageIs(AsyncCommandExecuted);
		}, WaitTime);

		for (auto message : *msgs)
		{
			$HandleMessage(MessageReceived);
			$HandleMessage(ProtocolFailure);
			$HandleMessage(ShutdownRequest);
			$HandleMessage(AsyncExecutionFailure);
			$HandleMessage(AsyncCommandExecuted);
		}
	}

	void Application::Handle(MessageReceived* message)
	{
		Logger->Information("Message received from {0}. Trying to interpret it.", message->UserMessage->Sender);

		std::string content;
		try
		{
			auto result = this->context->CommandExecutor->Execute(message->UserMessage);
			content = this->BuildSuccessResponse(result);
		}
		catch (Exceptions::NotFoundException ex)
		{
			Logger->Debug("Cannot find command for the message.");
			content = this->BuildErrorResponse("", CommandDoesNotExist, ERROR_SUCCESS);
		}
		catch (Exceptions::ExecutionException ex)
		{
			Logger->Debug("Cannot execute the command. Message: {0}, error code: {1}.", ex.what(), ex.ErrorCode);
			content = this->BuildErrorResponse("", ex.what(), ex.ErrorCode);
		}

		this->context->Messenger->Send(new SendMessage(content, message->UserMessage->Sender, message->UserMessage->SourceProtocol));
	}

	void Application::Handle(ProtocolFailure* message)
	{
		Logger->Error("Protocol {0} failed.", message->Protocol->Name);

		auto it = std::find_if(this->protocols.begin(), this->protocols.end(), [&](const ProtocolState& state)
		{
			return state.Protocol == message->Protocol;
		});
		if (it == this->protocols.end())
		{
			Logger->Fatal("Protocol {0} was not working at the time of the message. Possible cause: bug in the protocol plugin.");
			return;
		}

		it->IsWorking = false;
		if (!this->HasWorkingProtocol())
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

	void Application::Handle(AsyncExecutionFailure* message)
	{
		Logger->Debug("Cannot execute the command {0}. Message: {1}, error code: {2}.",
			message->Command->Name, message->Description, message->ErrorCode);
		std::string content = this->BuildErrorResponse(message->Command->Name,
			message->Description, message->ErrorCode);
		this->context->Messenger->Send(new SendMessage(content, message->Recipient, message->Protocol));
	}

	void Application::Handle(AsyncCommandExecuted* message)
	{
		Logger->Debug("Async command {0} executed successfully. Sending response.",
			message->Command->Name);
		std::string content = this->BuildRawSuccessResponse(message->Command->Name,
			message->Message, message->AdditionalData, true);
		this->context->Messenger->Send(new SendMessage(content, message->Recipient,
			message->Protocol));
	}

	std::string Application::BuildSuccessResponse(const Commands::CommandExecutionResults& result)
	{
		if (result.IsAsync)
		{
			return this->sendJSON ? "{ \"isAsync\": true }" : AsyncMessage;
		}
		else
		{
			return this->BuildRawSuccessResponse("", result.Message, result.AdditionalData, false);
		}
	}

	std::string Application::BuildRawSuccessResponse(const std::string& command, const std::string& message,
		std::shared_ptr<const jsonxx::Object> additionalData, bool isAsyncResponse)
	{
		if (this->sendJSON)
		{
			jsonxx::Object response;
			response << "command" << command;
			response << "message" << message;
			response << "isAsyncResponse" << isAsyncResponse;
			if (additionalData != nullptr)
			{
				response << "additionalData" << *additionalData;
			}
			return response.write(jsonxx::JSON);
		}
		else
		{
			return message;
		}
	}

	std::string Application::BuildErrorResponse(const std::string& command, const std::string& message, unsigned int systemError)
	{
		if (this->sendJSON)
		{
			jsonxx::Object response;
			response << "command" << command;
			response << "message" << message;
			response << "systemError" << systemError;
			response << "systemMessage" << (systemError == ERROR_SUCCESS ? "" : Other::FormatError(systemError));
			return response.write(jsonxx::JSON);
		}
		else if (systemError != ERROR_SUCCESS)
		{
			return  fmt::str(fmt::Format(ExecutionExceptionWithSystemErrorMessage, message, systemError, Other::FormatError(systemError)));
		}
		else
		{
			return fmt::str(fmt::Format(ExecutionExceptionMessage, message));
		}
	}

}