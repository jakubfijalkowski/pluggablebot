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
	 * Okre�la kontekst aplikacji, czyli wszystkie zale�no�ci z g��wnego poziomu.
	 */
	class PLUGIN_API ApplicationContext
	{
	public:
		/**
		* Messaging::Messenger u�ywany przez aplikacj�.
		*/
		Messaging::Messenger* const Messenger;

		/**
		 * Commands::ICommandExecutor u�ywany przez aplikacj�.
		 */
		Commands::ICommandExecutor* const CommandExecutor;

		/**
		 * Plugins::PluginManager u�ywany przez aplikacj�
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
		 * Ustawia Plugins::PluginManager, kt�ry musi by� tworzony po utworzeniu ApplicationContext.
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
