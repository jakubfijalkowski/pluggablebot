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
		/**
		 * \brief Wskaźnik na zdarzenie biblioteki libgadu.
		 */
		typedef std::shared_ptr<gg_event> GGEvent;

		/**
		 * \brief Lista kontaktów.
		 */
		typedef std::vector<uint32_t> ContactList;

		/**
		 * \brief Wrapper na libgadu, uproszczający kod GGProtocol. Klient ten jest
		 * asynchroniczny, z pominięciem niektórych metod.
		 *
		 * *Timeout* określa jak długo klient będzie czekał na wiadomości z serwera.
		 * Przy łączeniu z serwerem wartość ta jest mnożona przez ConnectTimeoutMultiplier,
		 * ponieważ operacja ta jest wywoływana synchronicznie.
		 *
		 * Do obsługi połączeń z serwerem Gadu-Gadu używana jest biblioteka
		 * [libgadu](http://libgadu.net/). Sposób obsługi znajduje się w dokumentacji
		 * w/w biblioteki.
		 */
		class GGClient
		{
		public:
			/**
			 * \brief Mnożnik czasu oczekiwania na połączenie.
			 */
			const static int ConnectTimeoutMultiplier = 30;

			/**
			 * \brief Inicjalizuje obiekt ustawiając niezbędne wartości.
			 *
			 * \param uid Numer użytkownika.
			 * \param password Hasło.
			 * \param status Status.
			 * \param statusDescription Opis.
			 * \param timeout Określa jak długo klient będzie czekał na wiadomości.
			 *                Wartość w milisekundach.
			 */
			GGClient(int uid, const std::string& password, int status, const std::string& statusDescription, int timeout);

			/**
			 * \brief Kończy połączenie(jeśli jeszcze nie zostało zakończone) i zwalnia używane zasoby.
			 */
			~GGClient();

			/**
			 * \brief Próbuje nawiązać połączenie z serwerem. Jest to wykonywane synchronicznie.
			 *
			 * Nie trzeba wywoływać Disconnect po nieudanej próbie połączenia.
			 *
			 * \param contacts Lista kontaktów, którą klient posiada.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy nie uda się połączyć z serwerem.
			 */
			void Connect(const ContactList& contacts);

			/**
			 * \brief Kończy połączenie z serwerem i zwalnia sesję.
			 */
			void Disconnect();

			/**
			 * \brief Pobiera zdarzenie z serwera GG. 
			 *
			 * Wewnętrznie obsługuje nagłe zerwanie połączenia z serwerem jak i mechanizm ping-pong.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy serwer nie odpowiadał zbyt długi czas.
			 */
			GGEvent HandleEvents();

			/**
			 * \brief Wysyła wiadomość do użytkownika o wskazanym numerze.
			 *
			 * \param receipent Numer odbiorcy.
			 * \param content Treść wiadomości.
			 */
			void SendMessage(uin_t receipent, const std::string& content);

			/**
			 * \brief Wysyła do nadawcy żądanie wysłania obrazka.
			 */
			void RequestImage(uin_t sender, uint32_t size, uint32_t crc32);

		private:
			static const int PingTime = 59;

			/**
			 * \brief Oczekuje wskazany czas na wiadomość z serwera.
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