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
	 * Główna część aplikacja, która zarządza poszczególnymi podsystemami aplikacji.
	 * Przed jej uruchomieniem należy zainicjować wszystkie rzeczy, które są pomocniecze,
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
		 * Inicjalizuje aplikacje i jej podsystemy. Ładuje konfiguracje, pluginy,
		 * konfiguruje je i ich zależności, ale nie startuje obsługi protokołów,
		 * ani żadnego z podsystemów.
		 *
		 * Rozgraniczenie na inicjalizację i uruchomienie istnieje tylko dlatego,
		 * by uprościć kod obu.
		 */
		void Initialize();

		/**
		 * Startuje wszystkie wtyczki obsługujące protokoły oraz rozpoczyna główną pętle komunikatów.
		 * Wyjście z tej metody następuje, gdy wszystkie wtczki odmówiły posłuszeństwa, użytkownik wyłączył
		 * aplikację, lub została wywołana metoda Shutdown.
		 * 
		 * \return Zwraca kod wyjścia aplikacji.
		 */
		ApplicationExitCode Run();

		/**
		 * Wyłącza aplikacje, zmuszając główny wątek do opuszczenia metody Run.
		 *
		 * Może być wywołana asynchronicznie.
		 */
		void Shutdown();

		/**
		 * Czyści obiekt po zakończeniu działania. Wywoływane przez główny wątek zaraz po
		 * opuszczeniu Run.
		 */
		void Deinitialize();

	private:
		bool HasWorkingProtocol();
		bool StartProtocols();
		void StopProtocols();

		void GetMessages();
		void Handle(Messages::MessageReceived* message);
		void Handle(Messages::ShutdownRequest* message);
		void Handle(Messages::ProtocolFailure* message);

		Logging::LoggerPointer Logger;

		jsonxx::Object configuration;
		std::unique_ptr<ApplicationContext> context;

		std::vector<ProtocolState> protocols;

		ApplicationExitCode exitCode;
		bool exiting;
	};

}