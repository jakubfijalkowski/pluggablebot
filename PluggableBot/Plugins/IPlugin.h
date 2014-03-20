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
		 * Interfejs u�ywany do wst�pnej komunikacji mi�dzy aplikacj� a wtyczkami.
		 *
		 * Po za�adowaniu(u�ywaj�c metody \a CreatePlugin ) wtyczka jest konfigurowana,
		 * nast�pnie pobierane s� udost�pniane przez ni� interfejsy.
		 */
		class IPlugin
		{
		public:
			/**
			 * Pobiera nazw� wtyczki, u�ywan� m.in. do okre�lenia sekcji w pliku konfiguracyjnym.
			 */
			virtual const std::wstring& GetName() = 0;

			/**
			 * Konfiguruje wtyczk�, u�ywaj�c ustawie� wczytanych z odpowiedniej sekcji pliku konfiguracyjnego.
			 */
			// TODO: zmie� typ konfiguracji
			virtual void Configure(const void* configuration) = 0;

			/**
			 * Pobiera list� komend obs�ugiwanych przez wtyczk�.
			 */
			virtual std::shared_ptr<std::vector<Commands::CommandPointer>> GetSupportedCommands() = 0;

			/**
			 * Pobiera list� protoko��w obs�ugiwanych przez wtyczk�.
			 */
			virtual std::shared_ptr<std::vector<ProtocolPointer>> GetSupportedProtocols() = 0;

			virtual ~IPlugin() { }
		};
		
		/**
		 * Okre�la sygnatur� metody u�ywanej przez loader do za�adowania wtyczki.
		 * Metoda ta powinna by� dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "r�cznie".
		 */
		typedef IPlugin* (*CreatePluginMethod)();

		/**
		 * Okre�la sygnatur� metody u�ywanej przez loader do zwolnienia wtyczki.
		 * Metoda ta powinna by� dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "r�cznie".
		 */
		typedef void (*DeletePluginMethod)(IPlugin* plugin);

	}
}