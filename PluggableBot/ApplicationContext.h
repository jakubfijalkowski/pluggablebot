#pragma once
#include <memory>
#include "Commands/ICommandExecutor.h"
#include "Messaging/Messenger.h"
#include "Plugins/PluginManager.h"

namespace PluggableBot
{

	/**
	 * Okre�la kontekst aplikacji, czyli wszystkie zale�no�ci z g��wnego poziomu.
	 */
	class ApplicationContext
	{
	public:
		/**
		 * Commands::ICommandExecutor u�ywany przez aplikacj�.
		 */
		const std::unique_ptr<Commands::ICommandExecutor> CommandExecutor;

		/**
		 * Messaging::Messenger u�ywany przez aplikacj�.
		 */
		const std::unique_ptr<Messaging::Messenger> Messenger;

		/**
		 * Plugins::PluginManager u�ywany przez aplikacj�
		 */
		const std::unique_ptr<Plugins::PluginManager> Plugins;

		/**
		 * Inicjalizuje kontekst. Wszystkie zale�no�ci przekazywane s� na w�asno��.
		 */
		ApplicationContext(Commands::ICommandExecutor* commandExecutor, Messaging::Messenger* messenger,
			Plugins::PluginManager* plugins)
			: CommandExecutor(commandExecutor), Messenger(messenger), Plugins(plugins)
		{ }
	};

}
