#pragma once
#include <memory>
#include "Commands/ICommandExecutor.h"
#include "Messaging/Messenger.h"

namespace PluggableBot
{
	
	/**
	 * G��wna aplikacja, kt�ra zarz�dza poszczeg�lnymi podsystemami aplikacji.
	 * Przed jej uruchomieniem nale�y zainicjowa� wszystkie rzeczy, kt�re s� pomocniecze,
	 * np. Logger.
	 */
	class Application
	{
	public:
		/**
		 * Pobiera Commands::ICommandExecutor u�ywany przez aplikacj�.
		 */
		const Commands::ICommandExecutor* GetCommandExecutor()
		{

		}
		
		/**
		 * Pobiera Commands::IParser u�ywany przez aplikacj�.
		 */
		const Commands::IParser* GetParser()
		{

		}

		/**
		 * Pobiera Messageing::Messenger u�ywanego przez aplikacj�.
		 */
		const Messaging::Messenger* GetMessenger()
		{

		}

		/**
		 * Inicjalizuje aplikacje i jej podsystemy. �aduje konfiguracje, pluginy,
		 * konfiguruje je i ich zale�no�ci, ale nie startuje obs�ugi protoko��w.
		 *
		 * Rozgraniczenie na inicjalizacj� i uruchomienie istnieje tylko dlatego,
		 * by upro�ci� kod obu.
		 */
		void Initialize();

		/**
		 * Startuje wszystkie wtyczki obs�uguj�ce protoko�y oraz rozpoczyna g��wn� p�tle komunikat�w.
		 * Wyj�cie z tej metody nast�puje, gdy wszystkie wtczki odm�wi�y pos�usze�stwa, u�ytkownik wy��czy�
		 * aplikacj�, lub zosta�a wywo�ana metoda Shutdown.
		 * 
		 * \return Zwraca kod wyj�cia aplikacji.
		 */
		int Run();

		/**
		 * Wy��cza aplikacje, zmusz�j�� g��wny w�tek do opuszczenia metody Run.
		 */
		void Shutdown();
	};

}