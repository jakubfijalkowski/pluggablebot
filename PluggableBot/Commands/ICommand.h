#pragma once
#include <memory>
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
			 * Okreœla, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			const bool IsAsync;

			/**
			 * Treœæ wiadomoœci maj¹cej byæ odpowiedzi¹.
			 */
			const std::wstring Message;

			/**
			 * Obiekt bêd¹cy dodatkowymi danymi. Jest opcjonalny(mo¿e byæ nullptr).
			 */
			// TODO: zmieniæ typ na w³aœciwy
			const void* const AdditionalData;

			/**
			 *Inicjalizuje obiekt.
			 */
			CommandExecutionResults(const std::wstring& message, bool isAsync = false, void* additionalData = nullptr)
				: IsAsync(isAsync), Message(message), AdditionalData(additionalData)
			{ }
		};

		/**
		 * Interfejs dla komend. Dostarcza podstawowych informacji o komendzie oraz obs³uguje jej wywo³anie.
		 */
		class ICommand
		{
		public:
			/**
			 * Nazwê komendy. U¿ywana tylko w przypadku, gdy u¿ytkownik chce dowiedzieæ siê, jakie
			 * komendy s¹ dostêpne.
			 */
			const std::wstring Name;

			/**
			 * Pobiera IMatcher, który jest odpowiedzialny za dopasowanie wiadomoœci do komendy.
			 */
			virtual const IMatcher* GetMatcher() = 0;

			/**
			 * Wykonuje metodê i zwraca odpowiedŸ która zostanie dostarczona u¿ytkownikowi.
			 * By zg³osiæ b³¹d, metoda powinna rzuciæ wyj¹tek dziedzicz¹cy z ExecutionException lub jego samego.
			 *
			 * \exception ExecutionException Rzucany, gdy nie powiod³o siê wykonanie metody.
			 */
			virtual CommandExecutionResults Execute() = 0;

		protected:
			ICommand(std::unique_ptr<IMatcher> matcher)
			{

			}
		};

	}
}