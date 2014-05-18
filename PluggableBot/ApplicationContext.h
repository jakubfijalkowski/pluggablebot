#pragma once
#include <memory>
#include "Commands/ICommandExecutor.h"
#include "Messaging/Messenger.h"
#include "Plugins/PluginManager.h"

namespace PluggableBot
{

	/**
	 * Okreœla kontekst aplikacji, czyli wszystkie zale¿noœci z g³ównego poziomu.
	 */
	class ApplicationContext
	{
	public:
		/**
		 * Commands::ICommandExecutor u¿ywany przez aplikacjê.
		 */
		const std::unique_ptr<Commands::ICommandExecutor> CommandExecutor;

		/**
		 * Messaging::Messenger u¿ywany przez aplikacjê.
		 */
		const std::unique_ptr<Messaging::Messenger> Messenger;

		/**
		 * Plugins::PluginManager u¿ywany przez aplikacjê
		 */
		const std::unique_ptr<Plugins::PluginManager> Plugins;

		/**
		 * Inicjalizuje kontekst. Wszystkie zale¿noœci przekazywane s¹ na w³asnoœæ.
		 */
		ApplicationContext(Commands::ICommandExecutor* commandExecutor, Messaging::Messenger* messenger,
			Plugins::PluginManager* plugins)
			: CommandExecutor(commandExecutor), Messenger(messenger), Plugins(plugins)
		{ }
	};

}
