#include "Commands/CommandExecutionResults.h"
#include "Commands/ExecutionContext.h"
#include "Exceptions/ExecutionException.h"
#include "Commands/ICommand.h"
#include "Commands/ICommandExecutor.h"
#include "Commands/IMatcher.h"
#include "Commands/IParser.h"
#include "Commands/ParseResults.h"
#include "Exceptions/NotFoundException.h"
#include "Logging/Logger.h"
#include "Logging/IOutput.h"
#include "Logging/LogFactory.h"
#include "Messaging/IMessage.h"
#include "Messaging/Messenger.h"
#include "Plugins/IPlugin.h"
#include "Plugins/PluginManager.h"
#include "IProtocol.h"
#include "UserMessage.h"
using namespace PluggableBot;

int main()
{
	Logging::LogFactory::AddOutput(new Logging::ConsoleOutput());

	Plugins::PluginManager manager(nullptr);
	jsonxx::Object o;
	manager.Configure(o);

	manager.Load();
	manager.Unload();
	system("PAUSE");
}