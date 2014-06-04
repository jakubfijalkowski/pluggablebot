#pragma once
#include <string>
#include "Config.h"

namespace PluggableBot
{

	/**
	 * \brief Interfejs dla klas obsługujących protokoły sieciowe.
	 *
	 * Metody tej klasy nie powinny bezpośrednio rzucać wyjątkami z racji tego,
	 * że i tak właściwa obsługa dzieje się na osobnym wątku. Każda implementacja
	 * powinna próbować obsłużyć błąd samodzielnie, a gdy to się nie uda, powinna
	 * wysłać odpowiednią wiadomość, na którą zareaguje aplikacja.
	 *
	 * Komunikacja z resztą aplikacji odbywa się z wykorzystaniem obiektu typu
	 * Messenger. Klasa powinna tam zapisywać wiadomości od użytkowników
	 * jak również oczekiwać na ewentualne wiadomości, które ma wysłać.
	 */
	class PLUGIN_API IProtocol
	{
	public:
		/**
		 * \brief Nazwa protokołu, dostępna w celach informacyjnych i do identyfikacji
		 * protokołu przez użytkownika.
		 */
		const std::string Name;

		/**
		 * \brief Rozpoczyna pracę obiektu obsługującego protokół.
		 * Powinna jak najszybciej przekierować obsługę na osobny wątek.
		 */
		virtual void Start() = 0;

		/**
		 * \brief Wymusza zatrzymanie wątku obsługującego protokół sieciowy.
		 */
		virtual void Stop() = 0;

		/**
		 * \brief Czyści pozostałości po obiekcie.
		 */
		virtual ~IProtocol() { }

	protected:
		/**
		 * \brief Inicjalizuje protokół.
		 */
		IProtocol(const std::string& name)
			: Name(name)
		{ }
	};

	/**
	 * \brief Wskaźnik na protokół.
	 * Protokoły będą przeważnie zawarte we wtyczkach, dlatego użycie `smart pointer`ów
	 * nie przyniosłoby wielu korzyści a wymagałoby dodatkowej uwagi.
	 */
	typedef IProtocol* ProtocolPointer;

}