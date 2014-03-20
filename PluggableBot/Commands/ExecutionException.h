#pragma once
#include <exception>
#include <string>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Wyj¹tek rzucany, gdy nie uda siê wykonaæ komendy.
		 *
		 * Zawiera podstawowe informacje o b³êdzie, tj. wiadomoœæ(u¿ywaj¹c GetMessage) i ewentualny kod,
		 * który jest zwracany jako dodatkowa wartoœæ.
		 */
		class ExecutionException
			: public std::exception
		{
		public:
			/**
			 * Pobiera kod b³êdu.
			 */
			int GetErrorCode() const
			{

			}

			/**
			 * Pobiera wiadomoœæ.
			 */
			const std::wstring& GetMessage() const
			{

			}
		};

	}
}