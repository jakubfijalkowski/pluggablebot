#pragma once
#include <memory>
#include <list>
#include <functional>
#include <Windows.h>
#include "IMessage.h"

namespace PluggableBot
{
	namespace Messaging
	{

		typedef std::function<bool(IMessage*)> MessagePredicate;
		typedef std::list<MessagePointer> MessageList;
		typedef std::shared_ptr<MessageList> MessageListPointer;

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
		 *
		 * Kolejno�� wiadomo�ci nie jest zachowana. Funkcje Get mog� zmienia� kolejno�� wiadomo�ci
		 * na li�cie, by przyspieszy� usuwanie elementu(zast�powany jest ostatnim, zamiast przesuni�cia
		 * wszystkich element�w).
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
			void Push(MessagePointer message);

			/**
			 * Badziej przejrzysta wersja Get(type, 0);
			 */
			MessagePointer TryGet(int type)
			{
				return this->Get(type, 0);
			}

			/**
			 * Badziej przejrzysta wersja Get(predicate, 0);
			 */
			MessageListPointer TryGet(MessagePredicate predicate)
			{
				return this->Get(predicate, 0);
			}

			/**
			 * Pobiera jedn� wiadomo�� z list, a je�li takowa nie istnieje - czeka a� si� pojawi
			 * i j� zwraca. Je�li czas oczekiwania zostanie przekroczony, zostaje zwr�cony nullptr.
			 *
			 * \param type Typ wiadomo�ci, kt�rej oczekujemy.
			 * \param timeout Maksymalny czas oczekiwania. Domy�lnie niesko�czono��.
			 */
			MessagePointer Get(int type, int timeout = INFINITE);

			/**
			 * Wybiera z listy wiadomo�ci, kt�re spe�niaj� wskazany warunek. Gdy nie ma wiadomo�ci
			 * spe�niaj�cych takie za�o�enia, czeka okre�lony czas do pojawienia si� PIERWSZEJ
			 * wiadomo�ci, kt�ra mo�e by� zwr�cona. Gdy czas oczekiwania zostanie przekroczony,
			 * zostanie zwr�cona pusta kolekcja wiadomo�ci.
			 *
			 * \param predicate Warunek, kt�ry musi zosta� spe�niony, by wiadomo�� by�a zwr�cona.
			 * \param timeout Maksymalny czas oczekiwania. Domy�lnie niesko�czono��.
			 */
			MessageListPointer Get(MessagePredicate predicate, int timeout = INFINITE);
		};

	}
}