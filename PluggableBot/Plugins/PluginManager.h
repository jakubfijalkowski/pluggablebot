#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "IPlugin.h"
#include "../Logging/LogFactory.h"
#include "../External/jsonxx.h"

namespace PluggableBot
{
	class ApplicationContext;

	namespace Plugins
	{

		/**
		 * Klasa zarz�dzaj�ca wtyczkami. Odpowiada za ich �adowanie, konfiguracj� oraz usuwanie,
		 * gdy ju� nie s� potrzebne. Udost�pnia te� metody agreguj�ce informacje udost�pniane przez wtyczki.
		 */
		class PluginManager
		{
		public:
			/**
			 * Inicjalizuje obiekt.
			 *
			 * \param context Kontekst aplikacji, kt�ra u�ywa managera.
			 */
			PluginManager(ApplicationContext* context);

			/*
			 * Wy�adowuje wtyczki, je�li nie zosta�y wy�adowane wcze�niej.
			 */
			~PluginManager();

			/**
			* Konfiguruje wtyczki, wyszukuj�� dla nich odpowiednie sekcje w pliku konfiguracyjnym.
			* Je�li sekcja konfiguracyjna dla danej wtyczki nie istnieje, przekazywany jest pusty obiekt.
			*
			* \param configuration G��wny w�ze� pliku konfiguracyjnego.
			*/
			void Configure(const jsonxx::Object& configuration);

			/**
			 * �aduje wszystkie wtyczki z lokalizacji przekazanej do konstruktora.
			 */
			void Load();

			/**
			 * Zwalnia zasoby po wtyczkach oraz wy�adowuje za�adowane biblioteki.
			 */
			void Unload();

			/**
			 * Agreguje obs�ugiwane komendy z wszystkich wtyczek.
			 */
			std::vector<Commands::CommandPointer> GetCombinedCommands();

			/**
			 * Agreguje obs�ugiwane protoko�y z wszystkich wtyczek.
			 */
			std::vector<ProtocolPointer> GetCombinedProtocols();

		private:
			void LoadPlugin(const char* pluginsPath, const char* pluginName);

			const Logging::LoggerPointer Logger;

			ApplicationContext* context;
			std::string pluginsPath;
			jsonxx::Object configuration;
			
			std::vector<std::tuple<IPlugin*, HMODULE, DeletePluginMethod>> plugins;
		};

	}
}