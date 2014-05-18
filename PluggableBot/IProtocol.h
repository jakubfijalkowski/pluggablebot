#pragma once
#include <string>
#include "Config.h"

namespace PluggableBot
{

	/**
	 * Interfejs dla klas obs�uguj�cych protoko�y sieciowe.
	 *
	 * Metody tej klasy nie powinny bezpo�rednio rzuca� wyj�tkami z racji tego,
	 * �e i tak w�a�ciwa obs�uga dzieje si� na osobnym w�tku. Ka�da implementacja
	 * powinna pr�bowa� obs�u�y� b��d samodzielnie, a gdy to si� nie uda, powinna
	 * wys�a� odpowiedni� wiadomo��, na kt�r� zareaguje aplikacja.
	 *
	 * Komunikacja z reszt� aplikacji odbywa si� z wykorzystaniem obiektu typu
	 * Messenger. Klasa powinna tam zapisywa� wiadomo�ci od u�ytkownik�w
	 * jak r�wnie� oczekiwa� na ewentualne wiadomo�ci, kt�re ma wys�a�.
	 */
	class PLUGIN_API IProtocol
	{
	public:
		/**
		 * Nazwa protoko�u, kt�ra mo�e by� u�ywana do, np., filtracji wiadomo�ci albo u�ywana do logowania.
		 */
		const std::string Name;

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

	protected:
		IProtocol(const std::string& name)
			: Name(name)
		{ }
	};

	typedef IProtocol* ProtocolPointer;

}