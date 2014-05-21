#pragma once
#include <vector>
#include <memory>
#include "../Config.h"
#include "ICommand.h"
#include "IParser.h"
#include "../Logging/LogFactory.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Określa funkcjonalność klas wykonujących komendy.
		 *
		 * Klasa przechowuje listę komend oraz informacje o parserze(pochodzące z zewnątrz). Komendy nie są
		 * przekazywane na własność, ponieważ mogą pochodzić z zewnętrznych bibliotek, co uniemożliwia
		 * zwalnianie ich w sposób domyślny.
		 */
		class PLUGIN_API ICommandExecutor
		{
		public:
			/**
			 * Typ określający kolekcję komend.
			 */
			typedef std::vector<CommandPointer> CommandList;

			/**
			 * Parser używany przez klasę.
			 */
			const std::unique_ptr<IParser> Parser;

			/**
			 * Pobiera listę komend zarejestrowanych w obiekcie.
			 *
			 * Lista komend nie jest dostępna w prosty sposób, ponieważ obiekt może wymagać np. dodatkowej
			 * synchronizacji w dostępie. Dodatkowo, komendy nie powinny być usuwane.
			 */
			virtual const CommandList& GetCommands() = 0;
			
			/**
			 * Dodaje komendy do listy obsługiwanych.
			 *
			 * \param from Lista komend do dodania.
			 */
			virtual void AddCommands(const std::vector<CommandPointer>& from) = 0;

			/**
			 * Próbuję wywołać komendę, która jest określona w tekście. Rzuca wyjątkiem, gdy nie uda się wykonanie metody.
			 *
			 * \exception ExecutionException Rzucane, gdy wystąpi błąd w trakcie wykonywania komendy.
			 * \exception NotFoundException Rzucane, gdy nie uda się odnaleźć wskazanej komendy.
			 */
			virtual CommandExecutionResults Execute(UserMessagePointer message) = 0;

			virtual ~ICommandExecutor() { }

		protected:
			/**
			 * Inicjalizuje obiekt.
			 *
			 * \param parser Używany parser, który przekazywany jest NA WYŁĄCZNOŚĆ.
			 */
			ICommandExecutor(IParser* parser)
				: Parser(parser)
			{ }
		};

		/**
		 * Domyślny \a {executor} komend. Spełnia podstawowe założenia projektu.
		 */
		class PLUGIN_API DefaultCommandExecutor
			: public ICommandExecutor
		{
		public:
			DefaultCommandExecutor(IParser* parser);

			virtual const CommandList& GetCommands()
			{
				return this->commands;
			}

			virtual void AddCommands(const std::vector<CommandPointer>& from);
			virtual CommandExecutionResults Execute(UserMessagePointer message);

		private:
			const Logging::LoggerPointer Logger;

			CommandList commands;
			int normalCommandOffset;
		};

	}
}