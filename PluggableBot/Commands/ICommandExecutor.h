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
		 * Okreœla funkcjonalnoœæ klas wykonuj¹cych komendy.
		 *
		 * Klasa przechowuje listê komend oraz informacje o parserze(pochodz¹ce z zewn¹trz). Komendy nie s¹
		 * przekazywane na w³asnoœæ, poniewa¿ mog¹ pochodziæ z zewnêtrznych bibliotek, co uniemo¿liwia
		 * zwalnianie ich w sposób domyœlny.
		 */
		class PLUGIN_API ICommandExecutor
		{
		public:
			/**
			 * Typ okreœlaj¹cy kolekcjê komend.
			 */
			typedef std::vector<CommandPointer> CommandList;

			/**
			 * Parser u¿ywany przez klasê.
			 */
			const std::unique_ptr<IParser> Parser;

			/**
			 * Pobiera listê komend zarejestrowanych w obiekcie.
			 *
			 * Lista komend nie jest dostêpna w prosty sposób, poniewa¿ obiekt mo¿e wymagaæ np. dodatkowej
			 * synchronizacji w dostêpie. Dodatkowo, komendy nie powinny byæ usuwane.
			 */
			virtual const CommandList& GetCommands() = 0;
			
			/**
			 * Dodaje komendy do listy obs³ugiwanych.
			 *
			 * \param from Lista komend do dodania.
			 */
			virtual void AddCommands(const std::vector<CommandPointer>& from) = 0;

			/**
			 * Próbujê wywo³aæ komendê, która jest okreœlona w tekœcie. Rzuca wyj¹tkiem, gdy nie uda siê wykonanie metody.
			 *
			 * \exception ExecutionException Rzucane, gdy wyst¹pi b³¹d w trakcie wykonywania komendy.
			 * \exception NotFoundException Rzucane, gdy nie uda siê odnaleŸæ wskazanej komendy.
			 */
			virtual CommandExecutionResults Execute(UserMessagePointer message) = 0;

			virtual ~ICommandExecutor() { }

		protected:
			/**
			 * Inicjalizuje obiekt.
			 *
			 * \param parser U¿ywany parser, który przekazywany jest NA WY£¥CZNOŒÆ.
			 */
			ICommandExecutor(IParser* parser)
				: Parser(parser)
			{ }
		};

		/**
		 * Domyœlny \a {executor} komend. Spe³nia podstawowe za³o¿enia projektu.
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