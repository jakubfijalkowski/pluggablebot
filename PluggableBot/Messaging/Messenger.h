#pragma once
#include <memory>
#include <Windows.h>
#include "IMessage.h"

namespace PluggableBot
{
	namespace Messaging
	{

		/**
		 * Pos�aniec, czy te� szyna wiadomo�ci, kt�ry synchronizuje dost�p do g��wnego elementu
		 * komunikacyjnego aplikacji.
		 *
		 * Klasa ta odpowiada za przekazywanie wiadomo�ci mi�dzy poszczeg�lnymi podsystemami
		 * aplikacji, ze szczeg�lnym uwzgl�dnieniem tych dzia�aj�cych na r�nych w�tkach
		 * (np. g��wnego w�tku aplikacji i w�tk�w obs�uguj�cych wtyczki czy wiadomo�ci
		 * asynchroniczne).
		 * Do synchronizacji dost�pu do listy u�ywana jest sekcja krytyczna, poniewa� ka�da
		 * z metod wymaga wy��cznego dost�pu. Jest to miejsce na ulepszenia, gdy� Get tak naprawd�
		 * opiera si� g��wnie na odczycie(i sprawdzeniu, czy dana wiadomo�� istnieje), ale poniewa�
		 * szukamy konkretnego typu wiadomo�ci, musieliby�my wykona� double-checking, co niekoniecznie
		 * musi pom�c, a na pewno skomplikuje implementacje.
		 * Dodatkowo u�ywane jest zdarzenie, by powiadomi� w�tki oczekuj�ce na wiadomo�ci, �e takowe
		 * nadesz�y.
		 */
		class Messenger
		{
		public:
			/**
			 * Wysy�a now� pust� wiadomo�� o wskazanym typie.
			 */
			template<typename TMessage> void Send()
			{
				this->Send(new TMessage());
			}

			/**
			 * Wysy�a wskazan� wiadomo��.
			 */
			void Push(IMessage* message)
			{
				this->Push(std::shared_ptr<IMessage>(message));
			}

			/**
			 * Wysy�a wskazan� wiadomo��.
			 */
			void Push(std::shared_ptr<IMessage> message);

			/**
			 * Pobiera jedn� wiadomo�� z listy, o ile istnieje. Je�li nie ma �adnych wiadomo�ci
			 * to zwraca nullptr.
			 *
			 * \param type Typ wiadomo�ci, kt�rej oczekujemy.
			 */
			std::shared_ptr<IMessage> TryGet(int type)
			{
				return this->Get(type, 0);
			}

			/**
			 * Pobiera jedn� wiadomo�� z list, a je�li takowa nie istnieje - czeka a� si� pojawi
			 * i j� zwraca. Je�li czas oczekiwania zostanie przekroczony, zostaje zwr�cony nullptr.
			 *
			 * \param type Typ wiadomo�ci, kt�rej oczekujemy.
			 */
			std::shared_ptr<IMessage> Get(int type, int timeout = INFINITE);
		};

	}
}