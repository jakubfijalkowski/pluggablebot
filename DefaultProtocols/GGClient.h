#pragma once
#include <libgadu/libgadu.h>
#include <string>
#include "ConnectionFailureException.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		/**
		 * Wrapper na libgadu, uproszczaj¹cy kod GGProtocol. Klient ten jest asynchroniczny, z pominiêciem niektórych metod.
		 *
		 * \a {Timeout} okreœla jak d³ugo klient bêdzie czeka³ na wiadomoœci z serwera. Przy ³¹czeniu z serwerem wartoœæ ta jest mno¿ona
		 * przez ConnectTimeoutMultiplier, poniewa¿ operacja ta jest wywo³ywana synchronicznie.
		 */
		class GGClient
		{
		public:
			/**
			 * Mno¿nik czasu oczekiwania na po³¹czenie.
			 */
			const static int ConnectTimeoutMultiplier = 30;

			/**
			 * Inicjalizuje obiekt ustawiaj¹c niezbêdne wartoœci.
			 *
			 * \param timeout Okreœla jak d³ugo klient bêdzie czeka³ na wiadomoœci. Wartoœæ w sekundach.
			 */
			GGClient(int uid, const std::string& password, int status, const std::string& statusDescription, int timeout);

			/**
			 * Koñczy po³¹czenie(jeœli jeszcze nie zosta³o zakoñczone) i zwalnia u¿ywane zasoby.
			 */
			~GGClient();

			/**
			 * Próbuje nawi¹zaæ po³¹czenie z serwerem. Jest to wykonywane synchronicznie.
			 *
			 * Nie trzeba wywo³ywaæ Disconnect po nieudanej próbie po³¹czenia.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy nie uda siê po³¹czyæ z serwerem.
			 */
			void Connect();

			/**
			 * Koñczy po³¹czenie z serwerem i zwalnia sesjê.
			 */
			void Disconnect();

		private:
			/**
			 * Oczekuje wskazany czas na wiadomoœæ z serwera.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy wyst¹pi³ problem z odebraniem wiadomoœci z serwera.
			 * \return Zwraca typ wiadomoœci zapisane w zmiennej event.
			 */
			gg_event* WaitForEvent(int timeout);

			int timeout;

			gg_login_params loginParams;
			gg_session *session;

			FD_SET readSet;
			FD_SET writeSet;
		};

	}
}