#pragma once

namespace PluggableBot
{

	/**
	 * Interfejs dla klas obs�uguj�cych protoko�y sieciowe.
	 *
	 * Metody tej klasy nie powinny bezpo�rednio rzuca� wyj�tkami z racji tego,
	 * �e i tak w�a�ciwa obs�uga dzieje si� na osobnym w�tku. Ka�da implementacja
	 * powinna pr�bowa� obs�u�y� b��d samodzielnie, a gdy to si� nie uda, powinna
	 * wys�a� odpowiedni� wiadomo��, na kt�r� zareaguje aplikacja.
	 */
	class IProtocol
	{
	public:
		/*
		 * Rozpoczyna prac� obiektu obs�uguj�cego protok�. Nie powinno zabiera� zbyt du�o czasu
		 * i jak najszybciej przekierowa� obs�ug� na osobny w�tek.
		 */
		virtual void Start() = 0;

		/**
		 * Wymusza zatrzymanie w�tku obs�uguj�cego protok� sieciowy.
		 */
		virtual void Stop() = 0;

		virtual ~IProtocol() { }
	};

}