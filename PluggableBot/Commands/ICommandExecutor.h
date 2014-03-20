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
		 * Interfejs okre�laj�cy, co klasa, kt�ra jest odpowiedzialna za wykonywnie metod, powinna udost�pnia�.
		 *
		 * Klasa przechowuje list� komend oraz informacje o parserze(pochodz�ce z zewn�trz). Komendy nie s�
		 * przekazywane na w�asno��, poniewa� mog� pochodzi� z zewn�trznych bibliotek, co uniemo�liwia
		 * zwalnianie ich w spos�b domy�lny - st�d shared_ptr.
		 */
		class ICommandExecutor
		{
		public:
			/**
			 * Typ okre�laj�cy kolekcj� komend.
			 */
			typedef std::vector<std::shared_ptr<ICommand>> CommandList;

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
			virtual const CommandList* GetCommands() = 0;
			
			/**
			 * Dodaje komend� do listy obs�ugiwanych.
			 */
			virtual void AddCommand(std::shared_ptr<ICommand> command);

			/**
			 * Pr�buj� wywo�a� komend�, kt�ra jest okre�lona w tek�cie. Rzuca wyj�tkiem, gdy nie uda si� wykonanie metody.
			 *
			 * \exception ExecutionException Rzucane, gdy nie uda si� dobra� komendy do tekstu, lub wyst�pi b��d w
			 *			  trakcie wykonywania komendy.
			 */
			virtual CommandExecutionResults Execute(std::wstring& text) = 0;

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

	}
}