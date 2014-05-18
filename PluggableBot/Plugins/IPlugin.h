#pragma once
#include <string>
#include <list>
#include <memory>
#include "../Commands/ICommand.h"
#include "../IProtocol.h"

namespace PluggableBot
{
	class ApplicationContext;

	namespace Plugins
	{

		/**
		 * Jest u¿ywany do wstêpnej komunikacji miêdzy aplikacj¹ a wtyczk¹. Odpowiada
		 * za zarz¹dzanie obiektami obs³uguj¹cymi komendy oraz protoko³y(musi je tworzyæ,
		 * gdy jest wczytywana/konfigurowana oraz zwalniaæ, gdy sama jest zwalniana).
		 *
		 * Po za³adowaniu(u¿ywaj¹c eksportowanej funkcji \a CreatePlugin) wtyczka jest
		 * konfigurowana(Configure), a nastêpnie pobierane s¹ udostêpniane przez ni¹
		 * funkcjonalnoœci. Gdy nie s¹ potrzebne ¿adne udostêpniane przez ni¹ komendy
		 * i protoko³y, zostaje zwolniona(u¿ywaj¹c eksportowanej funkcji \a DeletePlugin).
		 */
		class IPlugin
		{
		public:
			/**
			 * Pobiera nazwê wtyczki, u¿ywan¹ m.in. do okreœlenia sekcji w pliku konfiguracyjnym.
			 */
			virtual const std::string& GetName() = 0;

			/**
			 * Konfiguruje wtyczkê, u¿ywaj¹c ustawieñ wczytanych z odpowiedniej sekcji pliku konfiguracyjnego.
			 */
			virtual void Configure(const jsonxx::Object& configuration) = 0;

			/**
			 * Pobiera listê komend obs³ugiwanych przez wtyczkê.
			 */
			virtual const std::list<Commands::CommandPointer>* GetSupportedCommands() = 0;

			/**
			 * Pobiera listê protoko³ów obs³ugiwanych przez wtyczkê.
			 */
			virtual const std::list<ProtocolPointer>* GetSupportedProtocols() = 0;

			virtual ~IPlugin() { }
		};
		
		/**
		 * Okreœla sygnaturê metody u¿ywanej przez loader do za³adowania wtyczki.
		 * Metoda ta powinna byæ dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "rêcznie".
		 */
		typedef IPlugin* (*CreatePluginMethod)(ApplicationContext* context);

		/**
		 * Okreœla sygnaturê metody u¿ywanej przez loader do zwolnienia wtyczki.
		 * Metoda ta powinna byæ dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "rêcznie".
		 */
		typedef void (*DeletePluginMethod)(IPlugin* plugin);

	}
}