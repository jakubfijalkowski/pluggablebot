#include <Windows.h>
#include "Application.h"
#include "Logging/LogFactory.h"
using namespace PluggableBot;
using namespace PluggableBot::Logging;

static Application GlobalApplication;

BOOL WINAPI CtrlCHandler(DWORD dwCtrlType)
{
	GlobalApplication.Shutdown();
	return TRUE;
}

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( 670 );
#endif  

	SetConsoleCtrlHandler(CtrlCHandler, TRUE);

	LogFactory::AddOutput(new ConsoleOutput());
	//TODO: add logging to file.

	auto logger = LogFactory::GetLogger("Main");
	logger->Information("Application started. You can stop it using Ctrl+C combination.");
	logger->Debug("Starting main application.");

	GlobalApplication.Initialize();
	logger->Debug("Application initialized. Starting main loop.");

	auto exitCode = GlobalApplication.Run();
	logger->Information("Main loop stopped. Exiting.");

	GlobalApplication.Deinitialize();

	LogFactory::Unload();
	return exitCode;
}