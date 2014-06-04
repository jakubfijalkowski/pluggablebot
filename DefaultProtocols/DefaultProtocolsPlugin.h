#pragma once
#include <PluggableBot/Plugins/IPlugin.h>
#include <PluggableBot/Logging/LogFactory.h>

namespace PluggableBot
{
	/**
	 * \brief Przestrzeń nazw zawierająca pluginy obsługujące domyślne protokoły sieciowe.
	 */
	namespace DefaultProtocols
	{
		using namespace PluggableBot::Plugins;

		/**
		 * \brief Główna klasa plugin z obsługą podstawowych protokołów.
		 */
		class DefaultProtocolsPlugin
			: public IPlugin
		{
		public:
			/**
			 * \brief Inicjalizuje obiekt.
			 */
			DefaultProtocolsPlugin(ApplicationContext* context);

			/**
			 * \brief Zwalnia pozostałe zasoby.
			 */
			virtual ~DefaultProtocolsPlugin();

			/**
			 * \brief Pobiera nazwę protokołu - "DefaultProtocols".
			 */
			virtual const std::string& GetName() const;

			/**
			 * \brief Konfiguruje obiekt i wtyczkę GG.
			 */
			virtual void Configure(const jsonxx::Object& configuration);

			/**
			 * \brief Nieużywane. Zwraca pustą listę.
			 */
			virtual const CommandList* GetSupportedCommands() const;

			/**
			 * \brief Zwraca listę obsługiwanych protokołów.
			 */
			virtual const ProtocolList* GetSupportedProtocols() const;

		private:
			const Logging::LoggerPointer Logger;

			std::string name;
			ProtocolList suppotedProtocols;

			ApplicationContext* context;
		};

		extern "C"
		{
			/**
			 * \brief Tworzy obiekt DefaultProtocolsPlugin.
			 */
			__declspec(dllexport) IPlugin* CreatePlugin(ApplicationContext* context);

			/**
			 * \brief Zwalnia obiekt DefaultProtocolsPlugin.
			 */
			__declspec(dllexport) void DeletePlugin(IPlugin* plugin);
		}
	}
}