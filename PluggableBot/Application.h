#pragma once
#include <memory>
#include "Commands/ICommandExecutor.h"
#include "Messaging/Messenger.h"

namespace PluggableBot
{
	
	/**
	 * G³ówna aplikacja, która zarz¹dza poszczególnymi podsystemami aplikacji.
	 * Przed jej uruchomieniem nale¿y zainicjowaæ wszystkie rzeczy, które s¹ pomocniecze,
	 * np. Logger.
	 */
	class Application
	{
	public:
		/**
		 * Pobiera Commands::ICommandExecutor u¿ywany przez aplikacjê.
		 */
		const Commands::ICommandExecutor* GetCommandExecutor()
		{

		}
		
		/**
		 * Pobiera Commands::IParser u¿ywany przez aplikacjê.
		 */
		const Commands::IParser* GetParser()
		{

		}

		/**
		 * Pobiera Messageing::Messenger u¿ywanego przez aplikacjê.
		 */
		const Messaging::Messenger* GetMessenger()
		{

		}

		/**
		 * Inicjalizuje aplikacje i jej podsystemy. £aduje konfiguracje, pluginy,
		 * konfiguruje je i ich zale¿noœci, ale nie startuje obs³ugi protoko³ów.
		 *
		 * Rozgraniczenie na inicjalizacjê i uruchomienie istnieje tylko dlatego,
		 * by uproœciæ kod obu.
		 */
		void Initialize();

		/**
		 * Startuje wszystkie wtyczki obs³uguj¹ce protoko³y oraz rozpoczyna g³ówn¹ pêtle komunikatów.
		 * Wyjœcie z tej metody nastêpuje, gdy wszystkie wtczki odmówi³y pos³uszeñstwa, u¿ytkownik wy³¹czy³
		 * aplikacjê, lub zosta³a wywo³ana metoda Shutdown.
		 * 
		 * \return Zwraca kod wyjœcia aplikacji.
		 */
		int Run();

		/**
		 * Wy³¹cza aplikacje, zmusz¹j¹æ g³ówny w¹tek do opuszczenia metody Run.
		 */
		void Shutdown();
	};

}