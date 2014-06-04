#pragma once
#include <PluggableBot/Plugins/IPlugin.h>

namespace PluggableBot
{
	/**
	 * \brief Przestrzeń nazw zawierająca plugin do zarządzania plikami.
	 *
	 * Wszystkie wtyczki w tej przestrzeni nazw używają aktualnej ścieżki
	 * roboczej użytkownika, zapisanej w UserData. Ścieżka domyślnie
	 * ustawiana jest na katalog lokalny użytkownika, który uruchomił
	 * aplikację.
	 */
	namespace FilesystemPlugin
	{
		using namespace PluggableBot::Plugins;

		/**
		 * \brief Plugin z komendami do obsługi systemu plików.
		 */
		class FilesystemPlugin
			: public IPlugin
		{
		public:
			/**
			 * \brief Inicjalizuje obiekt.
			 */
			FilesystemPlugin(ApplicationContext* context);

			/**
			 * \brief Zwalnia pozostałe zasoby.
			 */
			virtual ~FilesystemPlugin();

			/**
			 * \brief Pobiera nazwę protokołu - "FilesystemPlugin".
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
			 * \brief Tworzy obiekt FilesystemPlugin.
			 */
			__declspec(dllexport) IPlugin* CreatePlugin(ApplicationContext* context);

			/**
			 * \brief Zwalnia obiekt FilesystemPlugin.
			 */
			__declspec(dllexport) void DeletePlugin(IPlugin* plugin);
		}
	}
}