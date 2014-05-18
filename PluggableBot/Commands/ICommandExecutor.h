#pragma once
#include <vector>
#include <memory>
#include "ICommand.h"
#include "IParser.h"
#include "../Logging/LogFactory.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Okre�la funkcjonalno�� klas wykonuj�cych komendy.
		 *
		 * Klasa przechowuje list� komend oraz informacje o parserze(pochodz�ce z zewn�trz). Komendy nie s�
		 * przekazywane na w�asno��, poniewa� mog� pochodzi� z zewn�trznych bibliotek, co uniemo�liwia
		 * zwalnianie ich w spos�b domy�lny.
		 */
		class ICommandExecutor
		{
		public:
			/**
			 * Typ okre�laj�cy kolekcj� komend.
			 */
			typedef std::vector<CommandPointer> CommandList;

			/**
			 * Parser u�ywany przez klas�.
			 */
			const std::unique_ptr<IParser> Parser;

			/**
			 * Pobiera list� komend zarejestrowanych w obiekcie.
			 *
			 * Lista komend nie jest dost�pna w prosty spos�b, poniewa� obiekt mo�e wymaga� np. dodatkowej
			 * synchronizacji w dost�pie. Dodatkowo, komendy nie powinny by� usuwane.
			 */
			virtual const CommandList& GetCommands() = 0;
			
			/**
			 * Dodaje komend� do listy obs�ugiwanych.
			 */
			virtual void AddCommand(CommandPointer command) = 0;

			/**
			 * Pr�buj� wywo�a� komend�, kt�ra jest okre�lona w tek�cie. Rzuca wyj�tkiem, gdy nie uda si� wykonanie metody.
			 *
			 * \exception ExecutionException Rzucane, gdy nie uda si� dobra� komendy do tekstu, lub wyst�pi b��d w
			 *			  trakcie wykonywania komendy.
			 */
			virtual CommandExecutionResults Execute(UserMessagePointer message) = 0;

			virtual ~ICommandExecutor() { }

		protected:
			/**
			 * Inicjalizuje obiekt.
			 *
			 * \param parser U�ywany parser, kt�ry przekazywany jest NA WY��CZNO��.
			 */
			ICommandExecutor(IParser* parser)
				: Parser(parser)
			{ }
		};

		/**
		 * Domy�lny \a {executor} komend. Spe�nia podstawowe za�o�enia projektu.
		 */
		class DefaultCommandExecutor
			: public ICommandExecutor
		{
		public:
			DefaultCommandExecutor(IParser* parser);

			virtual const CommandList& GetCommands()
			{
				return this->commands;
			}

			virtual void AddCommand(CommandPointer command);
			virtual CommandExecutionResults Execute(UserMessagePointer message);

		private:
			const Logging::LoggerPointer Logger;

			CommandList commands;
			int normalCommandOffset;
		};

	}
}