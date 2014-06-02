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
		 * Zapisuje tekst do pliku.
		 */
		class StoreTextCommand
			: public ICommand
		{
		public:
			StoreTextCommand(ApplicationContext* context);
			virtual const IMatcher* GetMatcher() const;
			virtual CommandExecutionResults Execute(const ExecutionContext& context);

		private:
			ApplicationContext* context;
			std::unique_ptr<SimpleMatcher> matcher;
		};
	}
}
