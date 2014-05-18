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
			 * \param pluginsPath �cie�ka(bezwzgl�dna) do folderu z wtyczkami.
			 */
			PluginManager(ApplicationContext* context, const std::string& pluginsPath)
				: context(context), pluginsPath(pluginsPath)
			{ }

			/*
			 * Wy�adowuje wtyczki, je�li nie zosta�y wy�adowane wcze�niej.
			 */
			~PluginManager()
			{
				if (!this->plugins.empty())
				{
					this->Unload();
				}
			}

			/**
			 * Pobiera list� wtyczek.
			 */
			const std::vector<IPlugin*>* GetPlugins() const
			{
				return &this->plugins;
			}

			/**
			 * �aduje wszystkie wtyczki z lokalizacji przekazanej do konstruktora.
			 */
			void Load();

			/**
			 * Konfiguruje wtyczki, wyszukuj�� dla nich odpowiednie sekcje w pliku konfiguracyjnym.
			 * Je�li sekcja konfiguracyjna dla danej wtyczki nie istnieje, przekazywany jest pusty obiekt.
			 *
			 * \param configuration G��wny w�ze� pliku konfiguracyjnego.
			 */
			void Configure(const void* configuration);

			/**
			 * Zwalnia zasoby po wtyczkach oraz wy�adowuje za�adowane biblioteki.
			 */
			void Unload();

			/**
			 * Agreguje obs�ugiwane komendy z wszystkich wtyczek.
			 */
			std::list<Commands::CommandPointer> GetCombinedCommands();

			/**
			 * Agreguje obs�ugiwane protoko�y z wszystkich wtyczek.
			 */
			//TODO: zastanowi� si� nad tym, czy u�y� zwyk�ego wska�nika, czy shared_ptr, vectora czy listy
			std::list<ProtocolPointer> GetCombinedProtocols();

		private:
			ApplicationContext* context;
			std::string pluginsPath;
			std::vector<IPlugin*> plugins;
		};

	}
}