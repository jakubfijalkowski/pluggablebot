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
		 * \brief Wysyła wiadomość do wskazanego użytkownika.
		 *
		 * Składnia: `send to="adres użytkownika" by="protokół" msg="wiadomość"`
		 */
		class SendCommand
			: public ICommand
		{
		public:
			/**
			 * \brief Inicjalizuje komendę.
			 */
			SendCommand(ApplicationContext* context);

			/**
			 * \brief Zwraca SimpleMatcher odpowiedzialny za dopasowanie komendy.
			 */
			virtual const IMatcher* GetMatcher() const;

			/**
			 * \brief Wywołuje komendę.
			 */
			virtual CommandExecutionResults Execute(const ExecutionContext& context);

		private:
			ApplicationContext* context;
			std::unique_ptr<SimpleMatcher> matcher;
		};
	}
}
