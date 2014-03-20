#pragma once
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
			 * Pobiera warto�� okre�laj�c�, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			bool IsAsync() const
			{

			}

			/**
			 * Pobiera tre�� wiadomo�ci maj�cej by� odpowiedzi�.
			 */
			const std::wstring* GetMessage() const
			{

			}

			/**
			 * Pobiera obiekt b�d�cy dodatkowymi danymi. Jest opcjonalny(mo�e zwr�ci� nullptr).
			 */
			const void* GetJSONObject() const
			{

			}
		};

		/**
		 * Interfejs dla komend. Dostarcza podstawowych informacji o komendzie oraz obs�uguje jej wywo�anie.
		 */
		class ICommand
		{
		public:
			/**
			 * Pobiera nazw� komendy. Metoda ta jest u�ywana tylko w przypadku, gdy u�ytkownik chce
			 * dowiedzie� si�, jakie komendy s� u�ywane.
			 */
			virtual const std::wstring& GetName() = 0;

			/**
			 * Pobiera IMatcher, kt�ry jest odpowiedzialny za dopasowanie wiadomo�ci do komendy.
			 */
			virtual IMatcher* GetMatcher() = 0;

			/**
			 * Wykonuje metod� i zwraca odpowied� kt�ra zostanie dostarczona u�ytkownikowi.
			 * By zg�osi� b��d, metoda powinna rzuci� wyj�tek dziedzicz�cy z ExecutionException lub jego samego.
			 *
			 * \exception ExecutionException Rzucany, gdy nie powiod�o si� wykonanie metody.
			 */
			virtual CommandExecutionResults Execute() = 0;
		};

	}
}