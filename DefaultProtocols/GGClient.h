#pragma once
#include <libgadu/libgadu.h>
#include <string>
#include <memory>
#include <vector>
#include <ctime>
#include "ConnectionFailureException.h"

#undef SendMessage

namespace PluggableBot
{
	namespace DefaultProtocols
	{
		typedef std::shared_ptr<gg_event> GGEvent;
		typedef std::vector<uint32_t> ContactList;

		/**
		 * Wrapper na libgadu, uproszczający kod GGProtocol. Klient ten jest asynchroniczny, z pominięciem niektórych metod.
		 *
		 * \a {Timeout} określa jak długo klient będzie czekał na wiadomości z serwera. Przy łączeniu z serwerem wartość ta jest mnożona
		 * przez ConnectTimeoutMultiplier, ponieważ operacja ta jest wywoływana synchronicznie.
		 */
		class GGClient
		{
		public:
			/**
			 * Mnożnik czasu oczekiwania na połączenie.
			 */
			const static int ConnectTimeoutMultiplier = 30;

			/**
			 * Inicjalizuje obiekt ustawiając niezbędne wartości.
			 *
			 * \param timeout Określa jak długo klient będzie czekał na wiadomości. Wartość w milisekundach.
			 */
			GGClient(int uid, const std::string& password, int status, const std::string& statusDescription, int timeout);

			/**
			 * Kończy połączenie(jeśli jeszcze nie zostało zakończone) i zwalnia używane zasoby.
			 */
			~GGClient();

			/**
			 * Próbuje nawiązać połączenie z serwerem. Jest to wykonywane synchronicznie.
			 *
			 * Nie trzeba wywoływać Disconnect po nieudanej próbie połączenia.
			 *
			 * \param contacts Lista kontaktów, którą klient posiada.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy nie uda się połączyć z serwerem.
			 */
			void Connect(const ContactList& contacts);

			/**
			 * Kończy połączenie z serwerem i zwalnia sesję.
			 */
			void Disconnect();

			/**
			 * Pobiera zdarzenie z serwera GG. 
			 *
			 * Obsługuje nagłe zerwanie połączenia z serwerem jak i mechanizm ping-pong.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy serwer nie odpowiadał zbyt długi czas.
			 */
			GGEvent HandleEvents();

			/**
			 * Wysyła wiadomość do użytkownika o wskazanym numerze.
			 *
			 * \param receipent Numer odbiorcy.
			 * \param content Treść wiadomości.
			 */
			void SendMessage(uin_t receipent, const std::string& content);

			/**
			 * Wysyła do nadawcy żądanie wysłania obrazka.
			 */
			void RequestImage(uin_t sender, uint32_t size, uint32_t crc32);

		private:
			static const int PingTime = 59;

			/**
			 * Oczekuje wskazany czas na wiadomość z serwera.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy wystąpił problem z odebraniem wiadomości z serwera.
			 * \return Zwraca typ wiadomości zapisane w zmiennej event.
			 */
			GGEvent WaitForEvent(int timeout);

			const int timeout;

			gg_login_params loginParams;
			gg_session *session;

			FD_SET readSet;
			FD_SET writeSet;

			time_t lastPingTime;
			bool pongReceived;
		};

	}
}