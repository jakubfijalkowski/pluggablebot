#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Commands/ICommand.h"
#include "../IProtocol.h"

namespace PluggableBot
{
	namespace Plugins
	{

		/**
		 * Interfejs u¿ywany do wstêpnej komunikacji miêdzy aplikacj¹ a wtyczkami.
		 *
		 * Po za³adowaniu(u¿ywaj¹c metody \a CreatePlugin ) wtyczka jest konfigurowana,
		 * nastêpnie pobierane s¹ udostêpniane przez ni¹ interfejsy.
		 */
		class IPlugin
		{
		public:
			/**
			 * Pobiera nazwê wtyczki, u¿ywan¹ m.in. do okreœlenia sekcji w pliku konfiguracyjnym.
			 */
			virtual const std::wstring& GetName() = 0;

			/**
			 * Konfiguruje wtyczkê, u¿ywaj¹c ustawieñ wczytanych z odpowiedniej sekcji pliku konfiguracyjnego.
			 */
			// TODO: zmieñ typ konfiguracji
			virtual void Configure(const void* configuration) = 0;

			/**
			 * Pobiera listê komend obs³ugiwanych przez wtyczkê.
			 */
			virtual std::shared_ptr<std::vector<Commands::CommandPointer>> GetSupportedCommands() = 0;

			/**
			 * Pobiera listê protoko³ów obs³ugiwanych przez wtyczkê.
			 */
			virtual std::shared_ptr<std::vector<ProtocolPointer>> GetSupportedProtocols() = 0;

			virtual ~IPlugin() { }
		};
		
		/**
		 * Okreœla sygnaturê metody u¿ywanej przez loader do za³adowania wtyczki.
		 * Metoda ta powinna byæ dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "rêcznie".
		 */
		typedef IPlugin* (*CreatePluginMethod)();

		/**
		 * Okreœla sygnaturê metody u¿ywanej przez loader do zwolnienia wtyczki.
		 * Metoda ta powinna byæ dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "rêcznie".
		 */
		typedef void (*DeletePluginMethod)(IPlugin* plugin);

	}
}