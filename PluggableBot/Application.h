#pragma once
#include <memory>
#include "ApplicationContext.h"
#include "Logging/LogFactory.h"
#include "Messages/Messages.h"
#include "External/jsonxx.h"

namespace PluggableBot
{

	enum class ApplicationExitCode
		: int
	{
		Success,
		NoWorkingProtocols,
		ProtocolsFailed,
	};

	/**
	 * G³ówna czêœæ aplikacja, która zarz¹dza poszczególnymi podsystemami aplikacji.
	 * Przed jej uruchomieniem nale¿y zainicjowaæ wszystkie rzeczy, które s¹ pomocniecze,
	 * np. Logger.
	 */
	class Application
	{
	public:
		/**
		 * Inicjalizuje obiekt.
		 */
		Application()
			: exitCode(ApplicationExitCode::Success), exiting(false)
		{ }

		/**
		 * Inicjalizuje aplikacje i jej podsystemy. £aduje konfiguracje, pluginy,
		 * konfiguruje je i ich zale¿noœci, ale nie startuje obs³ugi protoko³ów,
		 * ani ¿adnego z podsystemów.
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
		ApplicationExitCode Run();

		/**
		 * Wy³¹cza aplikacje, zmuszaj¹c g³ówny w¹tek do opuszczenia metody Run.
		 *
		 * Mo¿e byæ wywo³ana asynchronicznie.
		 */
		void Shutdown();

		/**
		 * Czyœci obiekt po zakoñczeniu dzia³ania. Wywo³ywane przez g³ówny w¹tek zaraz po
		 * opuszczeniu Run.
		 */
		void Deinitialize();

	private:
		bool StartProtocols();
		void StopProtocols();

		void GetMessages();
		void Handle(Messages::MessageReceived* message);
		void Handle(Messages::ShutdownRequest* message);
		void Handle(Messages::ProtocolFailure* message);

		Logging::LoggerPointer Logger;

		jsonxx::Object configuration;
		std::unique_ptr<ApplicationContext> context;

		std::vector<ProtocolPointer> workingProtocols;

		ApplicationExitCode exitCode;
		bool exiting;
	};

}