#pragma once
#include <string>
#include <memory>
#include <Windows.h>
#include <system_error>
#include "Config.h"

namespace PluggableBot
{
	/**
	 * Przestrzeń nazw z funkcjami/stałymi, które nie są używane bezpośrednio
	 * przez aplikację, ale mają zastosowanie w więcej niż jednym pluginie.
	 */
	namespace Other
	{

		/**
		 * Odczytuje całą zawartość z hPipe(zakłada, że jest możliwość odczytu).
		 * Gdy odczytane zostanę wszystkie dostępne na dany moment dane, odczyt
		 * zostaje przerwany.
		 */
		PLUGIN_API std::string ReadFromPipe(HANDLE hPipe);

		/**
		 * Wywołuje polecenie we wskazanym katalogu roboczym, podpinając wewnętrzne
		 * \a {pipe}y pod standardowe wyjście i wyjście błędu. Czeka na zakończenie
		 * procesu, dopiero po tym odczytuje wyjście procesu.
		 *
		 * \exception std::system_error Rzucane, gdy nie powiedzie się uruchomienie
		 *		aplikacji lub utworzenie \a {pipe}.
		 */
		PLUGIN_API std::string CallSystemCommand(const std::string& command, const std::string& workingDirectory);

		/**
		 * Formatuje kod zwrócony przez GetLastError jako ciąg znaków UTF-8.
		 */
		PLUGIN_API std::string FormatError(DWORD code);

		/**
		 * Konwertuje ciąg znaków w UCS-16 na UTF-8.
		 */
		PLUGIN_API std::string WideCharToUTF8(const wchar_t* str);

		/**
		 * Konwertuje ciąg znaków w UTF-8 na UCS-16.
		 */
		PLUGIN_API std::shared_ptr<wchar_t> UTF8ToWideString(const std::string& str);

	}
}