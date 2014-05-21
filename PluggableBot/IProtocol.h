#pragma once
#include <string>
#include "Config.h"

namespace PluggableBot
{

	/**
	 * Interfejs dla klas obsługujących protokoły sieciowe.
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
		 * Nazwa protokołu, która może być używana do, np., filtracji wiadomości albo używana do logowania.
		 */
		const std::string Name;

		/*
		 * Rozpoczyna pracę obiektu obsługującego protokół. Nie powinno zabierać zbyt dużo czasu
		 * i jak najszybciej przekierować obsługę na osobny wątek.
		 */
		virtual void Start() = 0;

		/**
		 * Wymusza zatrzymanie wątku obsługującego protokół sieciowy.
		 */
		virtual void Stop() = 0;

		virtual ~IProtocol() { }

	protected:
		IProtocol(const std::string& name)
			: Name(name)
		{ }
	};

	typedef IProtocol* ProtocolPointer;

}