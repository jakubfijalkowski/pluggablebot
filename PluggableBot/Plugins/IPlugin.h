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
		 * Jest u�ywany do wst�pnej komunikacji mi�dzy aplikacj� a wtyczk�. Odpowiada
		 * za zarz�dzanie obiektami obs�uguj�cymi komendy oraz protoko�y(musi je tworzy�,
		 * gdy jest wczytywana/konfigurowana oraz zwalnia�, gdy sama jest zwalniana).
		 *
		 * Po za�adowaniu(u�ywaj�c eksportowanej funkcji \a CreatePlugin) wtyczka jest
		 * konfigurowana(Configure), a nast�pnie pobierane s� udost�pniane przez ni�
		 * funkcjonalno�ci. Gdy nie s� potrzebne �adne udost�pniane przez ni� komendy
		 * i protoko�y, zostaje zwolniona(u�ywaj�c eksportowanej funkcji \a DeletePlugin).
		 */
		class IPlugin
		{
		public:
			/**
			 * Pobiera nazw� wtyczki, u�ywan� m.in. do okre�lenia sekcji w pliku konfiguracyjnym.
			 */
			virtual const std::string& GetName() = 0;

			/**
			 * Konfiguruje wtyczk�, u�ywaj�c ustawie� wczytanych z odpowiedniej sekcji pliku konfiguracyjnego.
			 */
			virtual void Configure(const jsonxx::Object& configuration) = 0;

			/**
			 * Pobiera list� komend obs�ugiwanych przez wtyczk�.
			 */
			virtual const std::list<Commands::CommandPointer>* GetSupportedCommands() = 0;

			/**
			 * Pobiera list� protoko��w obs�ugiwanych przez wtyczk�.
			 */
			virtual const std::list<ProtocolPointer>* GetSupportedProtocols() = 0;

			virtual ~IPlugin() { }
		};
		
		/**
		 * Okre�la sygnatur� metody u�ywanej przez loader do za�adowania wtyczki.
		 * Metoda ta powinna by� dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "r�cznie".
		 */
		typedef IPlugin* (*CreatePluginMethod)(ApplicationContext* context);

		/**
		 * Okre�la sygnatur� metody u�ywanej przez loader do zwolnienia wtyczki.
		 * Metoda ta powinna by� dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "r�cznie".
		 */
		typedef void (*DeletePluginMethod)(IPlugin* plugin);

	}
}