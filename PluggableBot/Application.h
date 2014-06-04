#pragma once
#include <memory>
#include "ApplicationContext.h"
#include "Logging/LogFactory.h"
#include "Messages/Messages.h"
#include "External/jsonxx.h"

namespace PluggableBot
{
	/**
	 * \page pages_application_description Opis głównego obiektu aplikacji
	 *
	 * \tableofcontents
	 *
	 * \section brief_desc Ogólny opis
	 * Obiekt klasy Application odpowiada za zarządzanie główną częścią aplikacji.
	 * Nie odpowiada za inicjalizacji podsystemów takich jak Logging::Logger, czy
	 * inicjalizację konsoli. Odpowiedzialnością tej klasy jest spojenie podsystemów
	 * projektu i zarządzanie niektórymi wiadomościami przesyłanymi wewnątrz aplikacji.
	 *
	 * \section init Inicjalizacja
	 * Pierwszym krokiem do poprawnego wykorzystania aplikacji jest wywołanie metody
	 * Application::Initialize. Odpowiada ona za podstawową inicjalizację aplikacji,
	 * załadowanie konfiguracji, stworzenie i skonfigurowanie podsystemu wiadomości
	 * (Messaging::Messenger), interpretera komend(domyślnie używany jest
	 * Commands::DefaultCommandExecutor wraz z Commands::DefaultParser), oraz managera
	 * pluginów(Plugins::PluginManager).
	 *
	 * Po poprawnym utworzeniu tych systemów następuje inicjalizacja kontekstu aplikacji
	 * (ApplicationContext), który udostępnia główne podsystemy aplikacji wtyczką(głównie),
	 * jednocześnie izolując dostęp do głównego obiektu, który może nie być \a thread-safe.
	 *
	 * Kolejnym krokiem jest użycie Plugins::PluginManager do załadowania wtyczek. Pierwszym
	 * etapem jest poprawne skonfigurowanie go(udostępniając konfigurację wtyczką), a
	 * a następnie pozwolenie mu na załadowanie odpowiednich plików. Finalizacją tego kroku
	 * jest pobranie listy obsługiwanych komend i wtyczek.
	 *
	 * Etap ten nie rozpoczyna przetwarzania żadnych komunikatów ani też nie startuje żadnej
	 * wtyczki.
	 *
	 * \section main_loop Działanie aplikacji i pętla wiadomości
	 * Właściwa pętla rozpoczyna się od wywołania metody Application::Run. Następuje wtedy
	 * próba włączenia wszystkich wtyczek. Gdy to się nie powiedzie(tj. żadna wtyczka nie
	 * zostanie włączona) to zostanie zwrócony kod ApplicationExitCode::NoWorkingProtocols.
	 *
	 * Następnym etapem jest ciągła obsługa wiadomości. Klasa Application próbuje pobrać
	 * obsługiwane przez nią wiadomości z Messaging::Messenger(oczekując maksymalnie 100ms
	 * na przyjście wiadomości, potem sprawdzając po raz kolejny na siłę). Klasa ta obsługuje
	 * następujące wiadomości:
	 *   - Messages::MessageReceived - próbuje zinterpretować komendę i odesłać użytkownikowi
	 *     odpowiedź.
	 *   - Messages::ShutdownRequest - kończy działanie pętli komunikatów
	 *   - Messages::ProtocolFailure - odznacza protokół jako niedziałający, kończąc działanie
	 *     aplikacji, gdy już żaden protokół nie pracuje.
	 *   - Messages::AsyncExecutionFailure - wysyła użytkownikowi informacje o błędzie
	 *     komendy asynchronicznej.
	 *   - Messages::AsyncCommandExecuted - wysyła użytkownikowi odpowiedź komendy
	 *     asynchronicznej.
	 *
	 * Gdy wystąpi błąd lub użytkownik zechce wyłączyć aplikację, zatrzymywane są wszystkie
	 * progokoły i metoda Application::Run kończy działanie.
	 *
	 * \section deinit Deinicjalizacja
	 * Deinicjalizacja jest prostym procesem polegającym na usunięciu wszystkich podsystemów
	 * w odpowiedniej kolejności.
	 *
	 * \section message_handling Przetwarzanie wiadomości
	 * Klasa Application jest również odpowiedzialna za przetwarzanie wiadomości użytkownika.
	 * Gdy nadejdzie odpowiednia wiadomość, kontrola przekazywana jest do
	 * Commands::ICommandExecutor. Gdy komenda wywołuje się synchronicznie, użytkownik otrzyma
	 * jedyną odpowiedź już w pierwszej wiadomości. Gdy komenda wywołuje się asynchronicznie,
	 * pierwszą wysłaną wiadomością będzie informacja o wywołaniu komendy w tle. Dopiero
	 * gdy komenda uzna, że jest w stanie wysłać odpowiedź, może to zrobić(używając
	 * Messages::AsyncCommandExecuted).
	 *
	 * Gdy komenda/komenda asynchroniczna zgłosi błąd rzucając wyjątkiem
	 * Exceptions::ExecutionException lub wysyłając wiadomość Messages::AsyncExecutionFailure,
	 * użytkownik zostanie powiadomiony o tym fakcie przez ustandaryzowaną wiadomość błędu.
	 *
	 * \sa
	 * \ref pages_json_spec
	 */

	/**
	 * \brief Kod wyjścia z głównej aplikacji.
	 *
	 * \sa
	 * \ref pages_application_description
	 */
	enum class ApplicationExitCode
		: int
	{
		/**
		 * \brief Aplikacja zakończyła się prawidłowo.
		 */
		Success,

		/**
		 * \brief Żaden z protokołów nie mógł wystartować.
		 */
		NoWorkingProtocols,
		 
		/**
		 * \brief Wszystkie protokoły przestały działać.
		 */
		ProtocolsFailed,
	};

	/**
	 * \brief Główna część aplikacja, która zarządza poszczególnymi podsystemami aplikacji.
	 *
	 * Przed jej uruchomieniem należy zainicjować wszystkie rzeczy, które są pomocniecze,
	 * np. Logger.
	 */
	class Application
	{
	public:
		/**
		 * \brief Inicjalizuje obiekt.
		 */
		Application()
			: exitCode(ApplicationExitCode::Success), exiting(false)
		{ }

		/**
		 * \brief Inicjalizuje aplikacje i jej podsystemy. Ładuje konfiguracje, pluginy,
		 * konfiguruje je i ich zależności, ale nie startuje obsługi protokołów,
		 * ani żadnego z podsystemów.
		 *
		 * Rozgraniczenie na inicjalizację i uruchomienie istnieje tylko dlatego,
		 * by uprościć kod obu.
		 */
		void Initialize();

		/**
		 * \brief Startuje wszystkie wtyczki obsługujące protokoły oraz rozpoczyna główną pętle komunikatów.
		 * 
		 * Wyjście z tej metody następuje, gdy wszystkie wtczki odmówiły posłuszeństwa, użytkownik wyłączył
		 * aplikację, lub została wywołana metoda Shutdown.
		 * 
		 * \return Zwraca kod wyjścia aplikacji.
		 */
		ApplicationExitCode Run();

		/**
		 * \brief Wyłącza aplikacje, zmuszając główny wątek do opuszczenia metody Run.
		 *
		 * Może być wywołana asynchronicznie.
		 */
		void Shutdown();

		/**
		 * \brief Czyści obiekt po zakończeniu działania. Wywoływane przez główny wątek zaraz po
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
		void Handle(Messages::AsyncExecutionFailure* message);
		void Handle(Messages::AsyncCommandExecuted* message);

		std::string BuildSuccessResponse(const Commands::CommandExecutionResults& result);
		std::string BuildRawSuccessResponse(const std::string& command, const std::string& message,
			std::shared_ptr<const jsonxx::Object> additionalData, bool isAsyncResponse);
		std::string BuildErrorResponse(const std::string& command, const std::string& message, unsigned int systemError);

		Logging::LoggerPointer Logger;

		jsonxx::Object configuration;
		bool sendJSON;
		std::unique_ptr<ApplicationContext> context;

		std::vector<ProtocolState> protocols;

		ApplicationExitCode exitCode;
		bool exiting;
	};

}