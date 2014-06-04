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
	 * \brief Określa stan protokołu.
	 */
	class ProtocolState
	{
	public:
		/**
		 * \brief Wskaźnik na protokół.
		 */
		const ProtocolPointer Protocol;

		/**
		 * \brief Określa, czy dany protokół pracuje.
		 */
		bool IsWorking;

		/**
		 * \brief Inicjalizuje obiekt.
		 */
		ProtocolState(ProtocolPointer pointer)
			: Protocol(pointer), IsWorking(false)
		{ }
	};

	typedef std::vector<const ProtocolState> ProtocolList;

	/**
	 * \brief Określa kontekst aplikacji, czyli wszystkie zależności, które mogą
	 * być wykorzystane przez podsystemy.
	 */
	class PLUGIN_API ApplicationContext
	{
	public:
		/**
		 * \brief Messaging::Messenger używany przez aplikację.
		 */
		Messaging::Messenger* const Messenger;

		/**
		 * \brief Commands::ICommandExecutor używany przez aplikację.
		 */
		Commands::ICommandExecutor* const CommandExecutor;

		/**
		 * \brief Dane użytkownika(UserData) używane przez aplikację.
		 */
		UserData UserData;

		/**
		 * \brief Plugins::PluginManager używany przez aplikację
		 */
		Plugins::PluginManager* GetPlugins() const
		{
			return this->plugins;
		}

		/**
		 * \brief Lista obsługiwanych protokołów załadowanych przez aplikację.
		 */
		const ProtocolList* const Protocols;

		/**
		 * \brief Inicializuje kontekst aplikacji.
		 */
		ApplicationContext(Messaging::Messenger* messenger, Commands::ICommandExecutor* executor, const ProtocolList* protocols)
			: Messenger(messenger), CommandExecutor(executor), plugins(nullptr), Protocols(protocols)
		{ }

		/**
		 * \brief Ustawia Plugins::PluginManager, który musi być tworzony po utworzeniu ApplicationContext.
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
