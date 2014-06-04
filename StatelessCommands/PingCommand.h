#pragma once
#include <memory>
#include <PluggableBot/ApplicationContext.h>
#include <PluggableBot/Commands/ICommand.h>

namespace PluggableBot
{
	namespace StatelessCommands
	{
		using namespace PluggableBot::Commands;

		/**
		 * \brief Pinguje podany adres IP i zwraca, asynchronicznie, dane.
		 *
		 * Komenda wykonuje siê asynchronicznie.
		 * Komenda u¿ywa do tego systemowego polecenia `ping`.
		 *
		 * Sk³adnia: `ping address="address"`
		 */
		class PingCommand
			: public ICommand
		{
		public:
			/**
			 * \brief Inicjalizuje komendê.
			 */
			PingCommand(ApplicationContext* context);

			/**
			 * \brief Zwraca SimpleMatcher odpowiedzialny za dopasowanie komendy.
			 */
			virtual const IMatcher* GetMatcher() const;

			/**
			 * \brief Wywo³uje komendê.
			 */
			virtual CommandExecutionResults Execute(const ExecutionContext& context);

		private:
			ApplicationContext* context;
			std::unique_ptr<SimpleMatcher> matcher;
		};
	}
}
