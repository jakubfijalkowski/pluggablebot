#pragma once
#include <string>
#include "Config.h"

namespace PluggableBot
{

	/**
	 * Interfejs dla klas obs³uguj¹cych protoko³y sieciowe.
	 *
	 * Metody tej klasy nie powinny bezpoœrednio rzucaæ wyj¹tkami z racji tego,
	 * ¿e i tak w³aœciwa obs³uga dzieje siê na osobnym w¹tku. Ka¿da implementacja
	 * powinna próbowaæ obs³u¿yæ b³¹d samodzielnie, a gdy to siê nie uda, powinna
	 * wys³aæ odpowiedni¹ wiadomoœæ, na któr¹ zareaguje aplikacja.
	 *
	 * Komunikacja z reszt¹ aplikacji odbywa siê z wykorzystaniem obiektu typu
	 * Messenger. Klasa powinna tam zapisywaæ wiadomoœci od u¿ytkowników
	 * jak równie¿ oczekiwaæ na ewentualne wiadomoœci, które ma wys³aæ.
	 */
	class PLUGIN_API IProtocol
	{
	public:
		/**
		 * Nazwa protoko³u, która mo¿e byæ u¿ywana do, np., filtracji wiadomoœci albo u¿ywana do logowania.
		 */
		const std::string Name;

		/*
		 * Rozpoczyna pracê obiektu obs³uguj¹cego protokó³. Nie powinno zabieraæ zbyt du¿o czasu
		 * i jak najszybciej przekierowaæ obs³ugê na osobny w¹tek.
		 */
		virtual void Start() = 0;

		/**
		 * Wymusza zatrzymanie w¹tku obs³uguj¹cego protokó³ sieciowy.
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