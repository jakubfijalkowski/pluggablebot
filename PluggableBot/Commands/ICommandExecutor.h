#pragma once
#include <vector>
#include <memory>
#include "ICommand.h"
#include "IParser.h"

namespace PluggableBot
{
	namespace Commands
	{
		/**
		 * Interfejs okreœlaj¹cy, co klasa, która jest odpowiedzialna za wykonywnie metod, powinna udostêpniaæ.
		 *
		 * Klasa przechowuje listê komend oraz informacje o parserze(pochodz¹ce z zewn¹trz). Komendy nie s¹
		 * przekazywane na w³asnoœæ, poniewa¿ mog¹ pochodziæ z zewnêtrznych bibliotek, co uniemo¿liwia
		 * zwalnianie ich w sposób domyœlny - st¹d shared_ptr.
		 */
		class ICommandExecutor
		{
		public:
			/**
			 * Typ okreœlaj¹cy kolekcjê komend.
			 */
			typedef std::vector<std::shared_ptr<ICommand>> CommandList;

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
			virtual const CommandList* GetCommands() = 0;
			
			/**
			 * Dodaje komendê do listy obs³ugiwanych.
			 */
			virtual void AddCommand(std::shared_ptr<ICommand> command);

			/**
			 * Próbujê wywo³aæ komendê, która jest okreœlona w tekœcie. Rzuca wyj¹tkiem, gdy nie uda siê wykonanie metody.
			 *
			 * \exception ExecutionException Rzucane, gdy nie uda siê dobraæ komendy do tekstu, lub wyst¹pi b³¹d w
			 *			  trakcie wykonywania komendy.
			 */
			virtual CommandExecutionResults Execute(std::wstring& text) = 0;

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

	}
}