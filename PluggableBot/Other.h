#pragma once
#include <string>
#include <Windows.h>
#include <system_error>
#include "Config.h"

namespace PluggableBot
{
	/**
	 * Przestrzeñ nazw z funkcjami/sta³ymi, które nie s¹ u¿ywane bezpoœrednio
	 * przez aplikacjê, ale maj¹ zastosowanie w wiêcej ni¿ jednym pluginie.
	 */
	namespace Other
	{

		/**
		 * Odczytuje ca³¹ zawartoœæ z hPipe(zak³ada, ¿e jest mo¿liwoœæ odczytu).
		 * Gdy odczytane zostanê wszystkie dostêpne na dany moment dane, odczyt
		 * zostaje przerwany.
		 */
		PLUGIN_API std::string ReadFromPipe(HANDLE hPipe);

		/**
		 * Wywo³uje polecenie we wskazanym katalogu roboczym, podpinaj¹c wewnêtrzne
		 * \a {pipe}y pod standardowe wyjœcie i wyjœcie b³êdu. Czeka na zakoñczenie
		 * procesu, dopiero po tym odczytuje wyjœcie procesu.
		 *
		 * \exception std::system_error Rzucane, gdy nie powiedzie siê uruchomienie
		 *		aplikacji lub utworzenie \a {pipe}.
		 */
		PLUGIN_API std::string CallSystemCommand(const std::string& command, const std::string& workingDirectory);

		/**
		 * Formatuje kod zwrócony przez GetLastError jako ci¹g znaków UTF-8.
		 */
		PLUGIN_API std::string FormatError(DWORD code);

	}
}