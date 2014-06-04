#pragma once
#include <PluggableBot/Plugins/IPlugin.h>

namespace PluggableBot
{
	/**
	 * \brief Przestrzeń nazw zawierająca plugin do obsługi komend bezstanowych.
	 */
	namespace StatelessCommands
	{
		using namespace PluggableBot::Plugins;

		/**
		 * \brief Plugin z podstawowymi, bezstanowymi komendami.
		 */
		class StatelessPlugin
			: public IPlugin
		{
		public:
			/**
			 * \brief Inicjalizuje obiekt.
			 */
			StatelessPlugin(ApplicationContext* context);

			/**
			 * \brief Zwalnia pozostałe zasoby.
			 */
			virtual ~StatelessPlugin();

			/**
			 * \brief Pobiera nazwę protokołu - "StatelessCommands".
			 */
			virtual const std::string& GetName() const;
			
			/**
			 * \brief Nieużywane. 
			 */
			virtual void Configure(const jsonxx::Object& configuration);
			
			/**
			 * \brief Zwraca listę obsługiwanych wtyczek.
			 */
			virtual const CommandList* GetSupportedCommands() const;
			
			/**
			 * \brief Nieużywane. Zwraca pustą listę. 
			 */
			virtual const ProtocolList* GetSupportedProtocols() const;

		private:
			std::string name;
			CommandList supportedCommands;

			ApplicationContext* context;
		};

		extern "C"
		{
			/**
			 * \brief Tworzy obiekt StatelessPlugin.
			 */
			__declspec(dllexport) IPlugin* CreatePlugin(ApplicationContext* context);

			/**
			 * \brief Zwalnia obiekt StatelessPlugin.
			 */
			__declspec(dllexport) void DeletePlugin(IPlugin* plugin);
		}
	}
}