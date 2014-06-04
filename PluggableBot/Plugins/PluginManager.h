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

	/**
	 * \brief Przestrzeń nazw zawierająca obsługę wtyczek.
	 */
	namespace Plugins
	{

		/**
		 * \brief Klasa zarządzająca wtyczkami. Odpowiada za ich ładowanie, konfigurację oraz
		 * usuwanie, gdy już nie są potrzebne. Udostępnia też metody agregujące informacje
		 * udostępniane przez wtyczki.
		 *
		 * Załadowanie wtyczek polega na wylistowaniu wszystkich plików DLL w katalogu wtyczek
		 * (określanym w pliku konfiguracyjnym) i próbie ich załadowania do pamięci.
		 * Gdy to się powiedzie, następuje próba wyszukania metod tworzących i usuwających
		 * interfejs IPlugin - CreatePluginMethod oraz DeletePluginMethod. Gdy ich nie ma,
		 * wtyczka jest odrzucana. Gdy są, tworzony jest interfejs IPlugin dla danej wtyczki
		 * a uchwyt do biblioteki jest zapisywany, by zostać później zwolnionym.
		 *
		 * \sa
		 * \ref IPlugin
		 * \ref pages_json_spec
		 */
		class PluginManager
		{
		public:
			/**
			 * \brief Inicjalizuje obiekt.
			 *
			 * \param context Kontekst aplikacji, która używa managera.
			 */
			PluginManager(ApplicationContext* context);

			/*
			 * \brief Wyładowuje wtyczki, jeśli nie zostały wyładowane wcześniej.
			 */
			~PluginManager();

			/**
			* \brief Konfiguruje wtyczki, wyszukująć dla nich odpowiednie sekcje w pliku konfiguracyjnym.
			* Jeśli sekcja konfiguracyjna dla danej wtyczki nie istnieje, przekazywany jest pusty obiekt.
			*
			* \param configuration Główny węzeł pliku konfiguracyjnego.
			*/
			void Configure(const jsonxx::Object& configuration);

			/**
			 * \brief Ładuje wszystkie wtyczki z lokalizacji przekazanej do konstruktora.
			 */
			void Load();

			/**
			 * \brief Zwalnia zasoby po wtyczkach oraz wyładowuje załadowane biblioteki.
			 */
			void Unload();

			/**
			 * \brief Agreguje obsługiwane komendy z wszystkich wtyczek.
			 */
			std::vector<Commands::CommandPointer> GetCombinedCommands();

			/**
			 * \brief Agreguje obsługiwane protokoły z wszystkich wtyczek.
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