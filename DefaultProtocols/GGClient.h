#pragma once
#include <libgadu/libgadu.h>
#include <string>
#include "ConnectionFailureException.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		/**
		 * Wrapper na libgadu, uproszczaj�cy kod GGProtocol. Klient ten jest asynchroniczny, z pomini�ciem niekt�rych metod.
		 *
		 * \a {Timeout} okre�la jak d�ugo klient b�dzie czeka� na wiadomo�ci z serwera. Przy ��czeniu z serwerem warto�� ta jest mno�ona
		 * przez ConnectTimeoutMultiplier, poniewa� operacja ta jest wywo�ywana synchronicznie.
		 */
		class GGClient
		{
		public:
			/**
			 * Mno�nik czasu oczekiwania na po��czenie.
			 */
			const static int ConnectTimeoutMultiplier = 30;

			/**
			 * Inicjalizuje obiekt ustawiaj�c niezb�dne warto�ci.
			 *
			 * \param timeout Okre�la jak d�ugo klient b�dzie czeka� na wiadomo�ci. Warto�� w sekundach.
			 */
			GGClient(int uid, const std::string& password, int status, const std::string& statusDescription, int timeout);

			/**
			 * Ko�czy po��czenie(je�li jeszcze nie zosta�o zako�czone) i zwalnia u�ywane zasoby.
			 */
			~GGClient();

			/**
			 * Pr�buje nawi�za� po��czenie z serwerem. Jest to wykonywane synchronicznie.
			 *
			 * Nie trzeba wywo�ywa� Disconnect po nieudanej pr�bie po��czenia.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy nie uda si� po��czy� z serwerem.
			 */
			void Connect();

			/**
			 * Ko�czy po��czenie z serwerem i zwalnia sesj�.
			 */
			void Disconnect();

		private:
			/**
			 * Oczekuje wskazany czas na wiadomo�� z serwera.
			 *
			 * \exception ConnectionFailureException Rzucany, gdy wyst�pi� problem z odebraniem wiadomo�ci z serwera.
			 * \return Zwraca typ wiadomo�ci zapisane w zmiennej event.
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