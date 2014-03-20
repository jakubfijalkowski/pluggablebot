#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Wyj�tek rzucany, gdy nie uda si� wykona� komendy.
		 *
		 * Zawiera podstawowe informacje o b��dzie, tj. wiadomo��(u�ywaj�c GetMessage) i ewentualny kod,
		 * kt�ry jest zwracany jako dodatkowa warto��.
		 */
		class ExecutionException
			: public std::exception
		{
		public:
			/**
			 * Pobiera kod b��du.
			 */
			int GetErrorCode() const
			{

			}

			/**
			 * Pobiera wiadomo��.
			 */
			const std::wstring& GetMessage() const
			{

			}
		};

	}
}