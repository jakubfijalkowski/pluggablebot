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
		 * \brief Określa funkcjonalność klas wykonujących komendy.
		 *
		 * Klasa przechowuje listę komend oraz informacje o parserze(pochodzące z zewnątrz). Komendy nie są
		 * przekazywane na własność, ponieważ mogą pochodzić z zewnętrznych bibliotek, co uniemożliwia
		 * zwalnianie ich w sposób domyślny.
		 *
		 * ### Zasada działania ###
		 * Po otrzymaniu wiadomości, następuje próba sparsowania jej a następnie dopasowania do jedej
		 * z istniejących komend. Gdy to się powiedzie, następuje przekazanie kontroli do komendy.
		 * Gdy nie uda się dopasować żadnej z komend, klasa zwraca błąd.
		 */
		class PLUGIN_API ICommandExecutor
		{
		public:
			/**
			 * \brief Typ określający kolekcję komend.
			 */
			typedef std::vector<CommandPointer> CommandList;

			/**
			 * \brief Parser używany przez klasę.
			 */
			const std::unique_ptr<IParser> Parser;

			/**
			 * \brief Pobiera listę komend zarejestrowanych w obiekcie.
			 *
			 * Lista komend nie jest dostępna w prosty sposób, ponieważ obiekt może wymagać np. dodatkowej
			 * synchronizacji w dostępie. Dodatkowo, komendy nie powinny być usuwane.
			 */
			virtual const CommandList& GetCommands() = 0;
			
			/**
			 * \brief Dodaje komendy do listy obsługiwanych.
			 *
			 * \param from Lista komend do dodania.
			 */
			virtual void AddCommands(const std::vector<CommandPointer>& from) = 0;

			/**
			 * \brief Próbuję wywołać komendę, która jest określona w tekście. Rzuca wyjątkiem, gdy nie uda się wykonanie metody.
			 *
			 * \exception ExecutionException Rzucane, gdy wystąpi błąd w trakcie wykonywania komendy.
			 * \exception NotFoundException Rzucane, gdy nie uda się odnaleźć wskazanej komendy.
			 */
			virtual CommandExecutionResults Execute(UserMessagePointer message) = 0;

			virtual ~ICommandExecutor() { }

		protected:
			/**
			 * \brief Inicjalizuje obiekt.
			 *
			 * \param parser Używany parser, który przekazywany jest NA WYŁĄCZNOŚĆ.
			 */
			ICommandExecutor(IParser* parser)
				: Parser(parser)
			{ }
		};

		/**
		 * \brief Domyślny `executor` komend. Spełnia podstawowe założenia projektu.
		 */
		class PLUGIN_API DefaultCommandExecutor
			: public ICommandExecutor
		{
		public:
			/**
			 * \brief Inicjalizuje obiekt.
			 */
			DefaultCommandExecutor(IParser* parser);


			/**
			 * \brief Pobiera listę komend zarejestrowanych w obiekcie.
			 */
			virtual const CommandList& GetCommands()
			{
				return this->commands;
			}
			
			/**
			 * \brief Dodaje komendy do listy obsługiwanych.
			 *
			 * \param from Lista komend do dodania.
			 */
			virtual void AddCommands(const std::vector<CommandPointer>& from);

			/**
			 * \brief Próbuje dopasować i wywołać komendę do danej wiadomości.
			 *
			 * \sa
			 * \ref ICommandExecutor::Execute
			 */
			virtual CommandExecutionResults Execute(UserMessagePointer message);

		private:
			const Logging::LoggerPointer Logger;

			CommandList commands;
			int normalCommandOffset;
		};

	}
}