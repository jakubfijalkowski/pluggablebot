#pragma once
#include <memory>
#include "IMatcher.h"
#include "CommandExecutionResults.h"
#include "ExecutionContext.h"
#include "ExecutionException.h"

namespace PluggableBot
{
	/**
	 * Przestrzeñ nazw zawieraj¹ca wszystkie klasy i interfejsy zwi¹zane z komendami.
	 */
	namespace Commands
	{

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
			const std::string Name;

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
			virtual CommandExecutionResults Execute(const ExecutionContext& context) = 0;

			virtual ~ICommand() { }
		};

		typedef ICommand* CommandPointer;

	}
}