#pragma once
#include <cassert>
#include <memory>
#include "Config.h"
#include "Commands/ICommandExecutor.h"
#include "Messaging/Messenger.h"
#include "Plugins/PluginManager.h"
#include "UserData.h"

namespace PluggableBot
{

	/**
	 * Określa kontekst aplikacji, czyli wszystkie zależności z głównego poziomu.
	 */
	class PLUGIN_API ApplicationContext
	{
	public:
		/**
		* Messaging::Messenger używany przez aplikację.
		*/
		Messaging::Messenger* const Messenger;

		/**
		 * Commands::ICommandExecutor używany przez aplikację.
		 */
		Commands::ICommandExecutor* const CommandExecutor;

		/**
		 * Dane użytkownika(UserData) używane przez aplikację.
		 */
		const UserData UserData;

		/**
		 * Plugins::PluginManager używany przez aplikację
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
		 * Ustawia Plugins::PluginManager, który musi być tworzony po utworzeniu ApplicationContext.
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
