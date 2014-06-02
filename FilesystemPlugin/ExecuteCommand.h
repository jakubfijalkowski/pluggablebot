#pragma once
#include <memory>
#include <PluggableBot/ApplicationContext.h>
#include <PluggableBot/Commands/ICommand.h>

namespace PluggableBot
{
	namespace FilesystemPlugin
	{
		using namespace PluggableBot::Commands;

		/**
		 * Wyświetla zawartość pliku spod wskazanej ścieżki.
		 */
		class ExecuteCommand
			: public ICommand
		{
		public:
			ExecuteCommand(ApplicationContext* context);
			virtual const IMatcher* GetMatcher() const;
			virtual CommandExecutionResults Execute(const ExecutionContext& context);

		private:
			ApplicationContext* context;
			std::unique_ptr<SimpleMatcher> matcher;
		};
	}
}
