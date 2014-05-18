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
	 * G��wna cz�� aplikacja, kt�ra zarz�dza poszczeg�lnymi podsystemami aplikacji.
	 * Przed jej uruchomieniem nale�y zainicjowa� wszystkie rzeczy, kt�re s� pomocniecze,
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
		 * Inicjalizuje aplikacje i jej podsystemy. �aduje konfiguracje, pluginy,
		 * konfiguruje je i ich zale�no�ci, ale nie startuje obs�ugi protoko��w,
		 * ani �adnego z podsystem�w.
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
		ApplicationExitCode Run();

		/**
		 * Wy��cza aplikacje, zmuszaj�c g��wny w�tek do opuszczenia metody Run.
		 *
		 * Mo�e by� wywo�ana asynchronicznie.
		 */
		void Shutdown();

		/**
		 * Czy�ci obiekt po zako�czeniu dzia�ania. Wywo�ywane przez g��wny w�tek zaraz po
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