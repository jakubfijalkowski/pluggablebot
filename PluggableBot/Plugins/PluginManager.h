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
		 * Klasa zarządzająca wtyczkami. Odpowiada za ich ładowanie, konfigurację oraz usuwanie,
		 * gdy już nie są potrzebne. Udostępnia też metody agregujące informacje udostępniane przez wtyczki.
		 */
		class PluginManager
		{
		public:
			/**
			 * Inicjalizuje obiekt.
			 *
			 * \param context Kontekst aplikacji, która używa managera.
			 */
			PluginManager(ApplicationContext* context);

			/*
			 * Wyładowuje wtyczki, jeśli nie zostały wyładowane wcześniej.
			 */
			~PluginManager();

			/**
			* Konfiguruje wtyczki, wyszukująć dla nich odpowiednie sekcje w pliku konfiguracyjnym.
			* Jeśli sekcja konfiguracyjna dla danej wtyczki nie istnieje, przekazywany jest pusty obiekt.
			*
			* \param configuration Główny węzeł pliku konfiguracyjnego.
			*/
			void Configure(const jsonxx::Object& configuration);

			/**
			 * Ładuje wszystkie wtyczki z lokalizacji przekazanej do konstruktora.
			 */
			void Load();

			/**
			 * Zwalnia zasoby po wtyczkach oraz wyładowuje załadowane biblioteki.
			 */
			void Unload();

			/**
			 * Agreguje obsługiwane komendy z wszystkich wtyczek.
			 */
			std::vector<Commands::CommandPointer> GetCombinedCommands();

			/**
			 * Agreguje obsługiwane protokoły z wszystkich wtyczek.
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