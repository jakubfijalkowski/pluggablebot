#pragma once
#include <memory>
#include "../Config.h"
#include "IMatcher.h"
#include "CommandExecutionResults.h"
#include "ExecutionContext.h"
#include "../Exceptions/ExecutionException.h"

namespace PluggableBot
{
	/**
	 * Przestrze� nazw zawieraj�ca wszystkie klasy i interfejsy zwi�zane z komendami.
	 */
	namespace Commands
	{

		/**
		 * Interfejs dla komend. Dostarcza podstawowych informacji o komendzie oraz obs�uguje jej wywo�anie.
		 */
		class PLUGIN_API ICommand
		{
		public:
			/**
			 * Nazw� komendy. U�ywana tylko w przypadku, gdy u�ytkownik chce dowiedzie� si�, jakie
			 * komendy s� dost�pne.
			 */
			const std::string Name;

			/**
			 * Pobiera IMatcher, kt�ry jest odpowiedzialny za dopasowanie wiadomo�ci do komendy.
			 */
			virtual const IMatcher* GetMatcher() const = 0;

			/**
			 * Wykonuje metod� i zwraca odpowied� kt�ra zostanie dostarczona u�ytkownikowi.
			 * By zg�osi� b��d, metoda powinna rzuci� wyj�tek dziedzicz�cy z ExecutionException lub jego samego.
			 *
			 * \exception ExecutionException Rzucany, gdy nie powiod�o si� wykonanie metody.
			 */
			virtual CommandExecutionResults Execute(const ExecutionContext& context) = 0;

			virtual ~ICommand() { }

		protected:
			ICommand(const std::string& name)
				: Name(name)
			{ }
		};

		typedef ICommand* CommandPointer;

	}
}