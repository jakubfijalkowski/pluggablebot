#pragma once
#include <memory>
#include <Windows.h>
#include "IMessage.h"

namespace PluggableBot
{
	namespace Messaging
	{

		/**
		 * Pos³aniec, czy te¿ szyna wiadomoœci, który synchronizuje dostêp do g³ównego elementu
		 * komunikacyjnego aplikacji.
		 *
		 * Klasa ta odpowiada za przekazywanie wiadomoœci miêdzy poszczególnymi podsystemami
		 * aplikacji, ze szczególnym uwzglêdnieniem tych dzia³aj¹cych na ró¿nych w¹tkach
		 * (np. g³ównego w¹tku aplikacji i w¹tków obs³uguj¹cych wtyczki czy wiadomoœci
		 * asynchroniczne).
		 * Do synchronizacji dostêpu do listy u¿ywana jest sekcja krytyczna, poniewa¿ ka¿da
		 * z metod wymaga wy³¹cznego dostêpu. Jest to miejsce na ulepszenia, gdy¿ Get tak naprawdê
		 * opiera siê g³ównie na odczycie(i sprawdzeniu, czy dana wiadomoœæ istnieje), ale poniewa¿
		 * szukamy konkretnego typu wiadomoœci, musielibyœmy wykonaæ double-checking, co niekoniecznie
		 * musi pomóc, a na pewno skomplikuje implementacje.
		 * Dodatkowo u¿ywane jest zdarzenie, by powiadomiæ w¹tki oczekuj¹ce na wiadomoœci, ¿e takowe
		 * nadesz³y.
		 */
		class Messenger
		{
		public:
			/**
			 * Wysy³a now¹ pust¹ wiadomoœæ o wskazanym typie.
			 */
			template<typename TMessage> void Send()
			{
				this->Send(new TMessage());
			}

			/**
			 * Wysy³a wskazan¹ wiadomoœæ.
			 */
			void Push(IMessage* message)
			{
				this->Push(std::shared_ptr<IMessage>(message));
			}

			/**
			 * Wysy³a wskazan¹ wiadomoœæ.
			 */
			void Push(std::shared_ptr<IMessage> message);

			/**
			 * Pobiera jedn¹ wiadomoœæ z listy, o ile istnieje. Jeœli nie ma ¿adnych wiadomoœci
			 * to zwraca nullptr.
			 *
			 * \param type Typ wiadomoœci, której oczekujemy.
			 */
			std::shared_ptr<IMessage> TryGet(int type)
			{
				return this->Get(type, 0);
			}

			/**
			 * Pobiera jedn¹ wiadomoœæ z list, a jeœli takowa nie istnieje - czeka a¿ siê pojawi
			 * i j¹ zwraca. Jeœli czas oczekiwania zostanie przekroczony, zostaje zwrócony nullptr.
			 *
			 * \param type Typ wiadomoœci, której oczekujemy.
			 */
			std::shared_ptr<IMessage> Get(int type, int timeout = INFINITE);
		};

	}
}