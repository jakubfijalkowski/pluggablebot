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
		 * Klasa zarz¹dzaj¹ca wtyczkami. Odpowiada za ich ³adowanie, konfiguracjê oraz usuwanie,
		 * gdy ju¿ nie s¹ potrzebne. Udostêpnia te¿ metody agreguj¹ce informacje udostêpniane przez wtyczki.
		 */
		class PluginManager
		{
		public:
			/**
			 * Inicjalizuje obiekt.
			 *
			 * \param context Kontekst aplikacji, która u¿ywa managera.
			 */
			PluginManager(ApplicationContext* context);

			/*
			 * Wy³adowuje wtyczki, jeœli nie zosta³y wy³adowane wczeœniej.
			 */
			~PluginManager();

			/**
			* Konfiguruje wtyczki, wyszukuj¹æ dla nich odpowiednie sekcje w pliku konfiguracyjnym.
			* Jeœli sekcja konfiguracyjna dla danej wtyczki nie istnieje, przekazywany jest pusty obiekt.
			*
			* \param configuration G³ówny wêze³ pliku konfiguracyjnego.
			*/
			void Configure(const jsonxx::Object& configuration);

			/**
			 * £aduje wszystkie wtyczki z lokalizacji przekazanej do konstruktora.
			 */
			void Load();

			/**
			 * Zwalnia zasoby po wtyczkach oraz wy³adowuje za³adowane biblioteki.
			 */
			void Unload();

			/**
			 * Agreguje obs³ugiwane komendy z wszystkich wtyczek.
			 */
			std::vector<Commands::CommandPointer> GetCombinedCommands();

			/**
			 * Agreguje obs³ugiwane protoko³y z wszystkich wtyczek.
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