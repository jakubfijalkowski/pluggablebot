#pragma once
#include "IMatcher.h"
#include "ExecutionException.h"

namespace PluggableBot
{
	/**
	 * Przestrzeñ nazw zawieraj¹ca wszystkie klasy i interfejsy zwi¹zane z komendami.
	 */
	namespace Commands
	{

		/**
		 * Wynik wykonywania komendy. Zawiera treœæ odpowiedzi i opcjonalny obiekt bêd¹cy dodatkowymi danymi(JSON).
		 */
		class CommandExecutionResults
		{
		public:
			/**
			 * Pobiera wartoœæ okreœlaj¹c¹, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			bool IsAsync() const
			{

			}

			/**
			 * Pobiera treœæ wiadomoœci maj¹cej byæ odpowiedzi¹.
			 */
			const std::wstring* GetMessage() const
			{

			}

			/**
			 * Pobiera obiekt bêd¹cy dodatkowymi danymi. Jest opcjonalny(mo¿e zwróciæ nullptr).
			 */
			const void* GetJSONObject() const
			{

			}
		};

		/**
		 * Interfejs dla komend. Dostarcza podstawowych informacji o komendzie oraz obs³uguje jej wywo³anie.
		 */
		class ICommand
		{
		public:
			/**
			 * Pobiera nazwê komendy. Metoda ta jest u¿ywana tylko w przypadku, gdy u¿ytkownik chce
			 * dowiedzieæ siê, jakie komendy s¹ u¿ywane.
			 */
			virtual const std::wstring& GetName() = 0;

			/**
			 * Pobiera IMatcher, który jest odpowiedzialny za dopasowanie wiadomoœci do komendy.
			 */
			virtual IMatcher* GetMatcher() = 0;

			/**
			 * Wykonuje metodê i zwraca odpowiedŸ która zostanie dostarczona u¿ytkownikowi.
			 * By zg³osiæ b³¹d, metoda powinna rzuciæ wyj¹tek dziedzicz¹cy z ExecutionException lub jego samego.
			 *
			 * \exception ExecutionException Rzucany, gdy nie powiod³o siê wykonanie metody.
			 */
			virtual CommandExecutionResults Execute() = 0;
		};

	}
}