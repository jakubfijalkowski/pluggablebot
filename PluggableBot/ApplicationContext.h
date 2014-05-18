#pragma once
#include <cassert>
#include <memory>
#include "Config.h"
#include "Commands/ICommandExecutor.h"
#include "Messaging/Messenger.h"
#include "Plugins/PluginManager.h"

namespace PluggableBot
{

	/**
	 * Okreœla kontekst aplikacji, czyli wszystkie zale¿noœci z g³ównego poziomu.
	 */
	class PLUGIN_API ApplicationContext
	{
	public:
		/**
		* Messaging::Messenger u¿ywany przez aplikacjê.
		*/
		Messaging::Messenger* const Messenger;

		/**
		 * Commands::ICommandExecutor u¿ywany przez aplikacjê.
		 */
		Commands::ICommandExecutor* const CommandExecutor;

		/**
		 * Plugins::PluginManager u¿ywany przez aplikacjê
		 */
		Plugins::PluginManager* GetPlugins()
		{
			return this->plugins;
		}

		/**
		 * Inicializuje kontekst aplikacji.
		 */
		ApplicationContext(Messaging::Messenger* messenger, Commands::ICommandExecutor* executor)
			: Messenger(messenger), CommandExecutor(executor), plugins(nullptr)
		{ }

		/**
		 * Ustawia Plugins::PluginManager, który musi byæ tworzony po utworzeniu ApplicationContext.
		 */
		void Set(Plugins::PluginManager* plugins)
		{
			assert(this->plugins == nullptr);
			this->plugins = plugins;
		}

	private:
		Plugins::PluginManager* plugins;
	};

}
