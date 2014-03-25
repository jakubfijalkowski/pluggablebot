#pragma once
#include <string>
#include <list>
#include "IPlugin.h"

namespace PluggableBot
{
	class Application;

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
			 * \param application Aplikacja, kt�ra u�ywa managera.
			 * \param pluginsPath �cie�ka(bezwzgl�dna) do folderu z wtyczkami.
			 */
			PluginManager(Application* application, const std::wstring& pluginsPath)
				: Application(application), PluginsPath(pluginsPath)
			{ }

			/*
			 * Wy�adowuje wtyczki, je�li nie zosta�y wy�adowane wcze�niej.
			 */
			~PluginManager()
			{
				if (!this->Plugins.empty())
					this->Unload();
			}

			/**
			 * Pobiera list� wtyczek.
			 */
			const std::vector<IPlugin*>* GetPlugins() const
			{
				return &this->Plugins;
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
			Application* Application;
			std::wstring PluginsPath;
			std::vector<IPlugin*> Plugins;
		};

	}
}