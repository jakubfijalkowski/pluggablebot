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
		 * Commands::ICommandExecutor u¿ywany przez aplikacjê.
		 */
		Commands::ICommandExecutor* GetCommandExecutor()
		{
			return this->executor.get();
		}

		/**
		 * Messaging::Messenger u¿ywany przez aplikacjê.
		 */
		Messaging::Messenger* GetMessenger()
		{
			return this->messenger.get();
		}

		/**
		 * Plugins::PluginManager u¿ywany przez aplikacjê
		 */
		Plugins::PluginManager* GetPlugins()
		{
			return this->plugins.get();
		}

		/**
		 * Ustawia u¿ywany Commands::ICommandExecutor. Przekazywany na w³asnoœæ.
		 */
		ApplicationContext& Set(Commands::ICommandExecutor* executor)
		{
			assert(!this->executor);
			std::unique_ptr<Commands::ICommandExecutor> tmp(executor);
			this->executor = std::move(tmp);
			return *this;
		}

		/**
		 * Ustawia u¿ywany Messaging::Messenger. Przekazywany na w³asnoœæ.
		 */
		ApplicationContext& Set(Messaging::Messenger* messenger)
		{
			assert(!this->messenger);
			std::unique_ptr<Messaging::Messenger> tmp(messenger);
			this->messenger = std::move(tmp);
			return *this;
		}

		/**
		 * Ustawia u¿ywany Plugins::PluginManager. Przekazywany na w³asnoœæ.
		 */
		ApplicationContext& Set(Plugins::PluginManager* plugins)
		{
			assert(!this->plugins);
			std::unique_ptr<Plugins::PluginManager> tmp(plugins);
			this->plugins = std::move(tmp);
			return *this;
		}

	private:
		std::unique_ptr<Commands::ICommandExecutor> executor;
		std::unique_ptr<Messaging::Messenger> messenger;
		std::unique_ptr<Plugins::PluginManager> plugins;
	};

}
