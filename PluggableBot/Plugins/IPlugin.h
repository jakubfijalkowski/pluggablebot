#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Commands/ICommand.h"
#include "../IProtocol.h"

namespace PluggableBot
{
	class ApplicationContext;

	namespace Plugins
	{

		/**
		 * \brief Jest używany do wstępnej komunikacji między aplikacją a wtyczką.
		 *
		 * Odpowiada za zarządzanie obiektami obsługującymi komendy oraz protokoły
		 * (musi je tworzyć, gdy jest wczytywana/konfigurowana oraz zwalniać, gdy
		 * sama jest zwalniana).
		 *
		 * Po załadowaniu(używając eksportowanej funkcji \a CreatePlugin) wtyczka jest
		 * konfigurowana(Configure), a następnie pobierane są udostępniane przez nią
		 * funkcjonalności. Gdy nie są potrzebne żadne udostępniane przez nią komendy
		 * i protokoły, zostaje zwolniona(używając eksportowanej funkcji \a DeletePlugin).
		 */
		class IPlugin
		{
		public:
			/*
			 * \brief Lista komend.
			 */
			typedef std::vector<Commands::CommandPointer> CommandList;
			
			/**
			 * \brief Lista protokołów.
			 */
			typedef std::vector<ProtocolPointer> ProtocolList;

			/**
			 * \brief Pobiera nazwę wtyczki, używaną m.in. do określenia sekcji w pliku konfiguracyjnym.
			 */
			virtual const std::string& GetName() const = 0;

			/**
			 * \brief Konfiguruje wtyczkę, używając ustawień wczytanych z odpowiedniej sekcji pliku konfiguracyjnego.
			 */
			virtual void Configure(const jsonxx::Object& configuration) = 0;

			/**
			 * \brief Pobiera listę komend obsługiwanych przez wtyczkę.
			 */
			virtual const CommandList* GetSupportedCommands() const = 0;

			/**
			 * \brief Pobiera listę protokołów obsługiwanych przez wtyczkę.
			 */
			virtual const ProtocolList* GetSupportedProtocols() const = 0;

			/**
			 * \brief Zwalnia wtyczkę(uwaga! wtyczka jest zwalniana używając DeletePluginMethod!).
			 */
			virtual ~IPlugin() { }
		};
		
		/**
		 * \brief Określa sygnaturę metody używanej przez loader do załadowania wtyczki.
		 *
		 * Metoda ta powinna być dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "ręcznie".
		 */
		typedef IPlugin* (*CreatePluginMethod)(ApplicationContext* context);

		/**
		 * \brief Określa sygnaturę metody używanej przez loader do zwolnienia wtyczki.
		 *
		 * Metoda ta powinna być dodatkowo "nieozdobiona"(tj. eksportowana w stylu C)
		 * oraz oznaczona atrybutem \a dllexport albo eksportowana "ręcznie".
		 */
		typedef void (*DeletePluginMethod)(IPlugin* plugin);

	}
}