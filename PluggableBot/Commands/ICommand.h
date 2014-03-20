#pragma once
#include <memory>
#include "IMatcher.h"
#include "ExecutionException.h"

namespace PluggableBot
{
	/**
	 * Przestrze� nazw zawieraj�ca wszystkie klasy i interfejsy zwi�zane z komendami.
	 */
	namespace Commands
	{

		/**
		 * Wynik wykonywania komendy. Zawiera tre�� odpowiedzi i opcjonalny obiekt b�d�cy dodatkowymi danymi(JSON).
		 */
		class CommandExecutionResults
		{
		public:
			/**
			 * Okre�la, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			const bool IsAsync;

			/**
			 * Tre�� wiadomo�ci maj�cej by� odpowiedzi�.
			 */
			const std::wstring Message;

			/**
			 * Obiekt b�d�cy dodatkowymi danymi. Jest opcjonalny(mo�e by� nullptr).
			 */
			// TODO: zmieni� typ na w�a�ciwy
			const void* const AdditionalData;

			/**
			 *Inicjalizuje obiekt.
			 */
			CommandExecutionResults(const std::wstring& message, bool isAsync = false, void* additionalData = nullptr)
				: IsAsync(isAsync), Message(message), AdditionalData(additionalData)
			{ }
		};

		/**
		 * Interfejs dla komend. Dostarcza podstawowych informacji o komendzie oraz obs�uguje jej wywo�anie.
		 */
		class ICommand
		{
		public:
			/**
			 * Nazw� komendy. U�ywana tylko w przypadku, gdy u�ytkownik chce dowiedzie� si�, jakie
			 * komendy s� dost�pne.
			 */
			const std::wstring Name;

			/**
			 * Pobiera IMatcher, kt�ry jest odpowiedzialny za dopasowanie wiadomo�ci do komendy.
			 */
			virtual const IMatcher* GetMatcher() = 0;

			/**
			 * Wykonuje metod� i zwraca odpowied� kt�ra zostanie dostarczona u�ytkownikowi.
			 * By zg�osi� b��d, metoda powinna rzuci� wyj�tek dziedzicz�cy z ExecutionException lub jego samego.
			 *
			 * \exception ExecutionException Rzucany, gdy nie powiod�o si� wykonanie metody.
			 */
			virtual CommandExecutionResults Execute() = 0;

		protected:
			ICommand(std::unique_ptr<IMatcher> matcher)
			{

			}
		};

	}
}