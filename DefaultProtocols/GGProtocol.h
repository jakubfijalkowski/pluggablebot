#pragma once
#include <PluggableBot/ApplicationContext.h>
#include <PluggableBot/IProtocol.h>
#include <PluggableBot/Logging/LogFactory.h>
#include <PluggableBot/External/jsonxx.h>
#include <thread>
#include <memory>
#include <vector>
#include "GGClient.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		/**
		 * \brief Określa stan konfiguracji.
		 */
		enum class ConfigurationStatus
		{
			/**
			 * \brief Poprawna.
			 */
			Valid,

			/**
			 * \brief Niepoprawna.
			 */
			Invalid,
			
			/**
			 * \brief Wtyczka została wyłączona.
			 */
			Disabled
		};

		/**
		 * \brief Obsługuje protokół GG.
		 *
		 * Obsługuje proste tekstowe wiadomości wysyłane w obie strony i odbieranie obrazków,
		 * więcej funkcji protokołu Gadu-Gadu nie jest obsługiwanych, a zdarzenia z nimi związane
		 * są ignorowane.
		 */
		class GGProtocol
			: public IProtocol
		{
		public:
			/**
			 * \brief Inicjalizuje wtyczke.
			 */
			GGProtocol(ApplicationContext* context, const jsonxx::Object& config);

			/**
			 * \brief Tworzy nowy wątek, który łączy i utrzymuje połączenie z serwerem.
			 */
			virtual void Start();

			/**
			 * \brief Zmusza wątek obsługujący połączenie do zatrzymania się.
			 */
			virtual void Stop();

			/**
			 * \brief Sprawdza, czy konfiguracja wtyczki podana przez użytkownika jest prawidłowa.
			 */
			static ConfigurationStatus CheckConfiguration(const jsonxx::Object& config);

		private:
			void ThreadMain(int& retryCount);
			bool TryConnect();
			bool HandleGGEvents();
			void HandleSystemEvents();

			const Logging::LoggerPointer Logger;

			const int MaxRetryCount;

			ApplicationContext* const context;

			bool shouldShutdown;
			std::thread main;
			std::unique_ptr<GGClient> client;
			ContactList contacts;
		};

	}
}