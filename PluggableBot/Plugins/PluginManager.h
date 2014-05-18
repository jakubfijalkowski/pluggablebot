#pragma once
#include <string>
#include <list>
#include "IPlugin.h"

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
			 * \param pluginsPath Œcie¿ka(bezwzglêdna) do folderu z wtyczkami.
			 */
			PluginManager(ApplicationContext* context, const std::string& pluginsPath)
				: context(context), pluginsPath(pluginsPath)
			{ }

			/*
			 * Wy³adowuje wtyczki, jeœli nie zosta³y wy³adowane wczeœniej.
			 */
			~PluginManager()
			{
				if (!this->plugins.empty())
				{
					this->Unload();
				}
			}

			/**
			 * Pobiera listê wtyczek.
			 */
			const std::vector<IPlugin*>* GetPlugins() const
			{
				return &this->plugins;
			}

			/**
			 * £aduje wszystkie wtyczki z lokalizacji przekazanej do konstruktora.
			 */
			void Load();

			/**
			 * Konfiguruje wtyczki, wyszukuj¹æ dla nich odpowiednie sekcje w pliku konfiguracyjnym.
			 * Jeœli sekcja konfiguracyjna dla danej wtyczki nie istnieje, przekazywany jest pusty obiekt.
			 *
			 * \param configuration G³ówny wêze³ pliku konfiguracyjnego.
			 */
			void Configure(const void* configuration);

			/**
			 * Zwalnia zasoby po wtyczkach oraz wy³adowuje za³adowane biblioteki.
			 */
			void Unload();

			/**
			 * Agreguje obs³ugiwane komendy z wszystkich wtyczek.
			 */
			std::list<Commands::CommandPointer> GetCombinedCommands();

			/**
			 * Agreguje obs³ugiwane protoko³y z wszystkich wtyczek.
			 */
			//TODO: zastanowiæ siê nad tym, czy u¿yæ zwyk³ego wskaŸnika, czy shared_ptr, vectora czy listy
			std::list<ProtocolPointer> GetCombinedProtocols();

		private:
			ApplicationContext* context;
			std::string pluginsPath;
			std::vector<IPlugin*> plugins;
		};

	}
}