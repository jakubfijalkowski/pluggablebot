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
	 * Przestrzeń nazw zawierająca wszystkie klasy i interfejsy związane z komendami.
	 */
	namespace Commands
	{

		/**
		 * Interfejs dla komend. Dostarcza podstawowych informacji o komendzie oraz obsługuje jej wywołanie.
		 */
		class PLUGIN_API ICommand
		{
		public:
			/**
			 * Nazwę komendy. Używana tylko w przypadku, gdy użytkownik chce dowiedzieć się, jakie
			 * komendy są dostępne.
			 */
			const std::string Name;

			/**
			 * Pobiera IMatcher, który jest odpowiedzialny za dopasowanie wiadomości do komendy.
			 */
			virtual const IMatcher* GetMatcher() const = 0;

			/**
			 * Wykonuje metodę i zwraca odpowiedź która zostanie dostarczona użytkownikowi.
			 * By zgłosić błąd, metoda powinna rzucić wyjątek dziedziczący z ExecutionException lub jego samego.
			 *
			 * \exception ExecutionException Rzucany, gdy nie powiodło się wykonanie metody.
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