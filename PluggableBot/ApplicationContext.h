#pragma once
#include <cassert>
#include <memory>
#include <vector>
#include "Config.h"
#include "Commands/ICommandExecutor.h"
#include "Messaging/Messenger.h"
#include "Plugins/PluginManager.h"
#include "UserData.h"

namespace PluggableBot
{

	/**
	 * Określa stan protokołu.
	 */
	class ProtocolState
	{
	public:
		/**
		 * Wskaźnik na protokół.
		 */
		const ProtocolPointer Protocol;

		/**
		 * Określa, czy dany protokół pracuje.
		 */
		bool IsWorking;

		ProtocolState(ProtocolPointer pointer)
			: Protocol(pointer), IsWorking(false)
		{ }
	};

	typedef std::vector<const ProtocolState> ProtocolList;

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
		UserData UserData;

		/**
		 * Plugins::PluginManager używany przez aplikację
		 */
		Plugins::PluginManager* GetPlugins() const
		{
			return this->plugins;
		}

		/**
		 * Lista obsługiwanych protokołów załadowanych przez aplikację.
		 */
		const ProtocolList* const Protocols;

		/**
		 * Inicializuje kontekst aplikacji.
		 */
		ApplicationContext(Messaging::Messenger* messenger, Commands::ICommandExecutor* executor, const ProtocolList* protocols)
			: Messenger(messenger), CommandExecutor(executor), plugins(nullptr), Protocols(protocols)
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
