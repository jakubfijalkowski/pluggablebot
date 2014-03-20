#pragma once

namespace PluggableBot
{

	/**
	 * Interfejs dla klas obs³uguj¹cych protoko³y sieciowe.
	 *
	 * Metody tej klasy nie powinny bezpoœrednio rzucaæ wyj¹tkami z racji tego,
	 * ¿e i tak w³aœciwa obs³uga dzieje siê na osobnym w¹tku. Ka¿da implementacja
	 * powinna próbowaæ obs³u¿yæ b³¹d samodzielnie, a gdy to siê nie uda, powinna
	 * wys³aæ odpowiedni¹ wiadomoœæ, na któr¹ zareaguje aplikacja.
	 */
	class IProtocol
	{
	public:
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
	};

}