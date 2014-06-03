#pragma once
#include <string>
#include <memory>
#include <Windows.h>
#include <system_error>
#include "Config.h"

namespace PluggableBot
{
	/**
	 * Przestrze� nazw z funkcjami/sta�ymi, kt�re nie s� u�ywane bezpo�rednio
	 * przez aplikacj�, ale maj� zastosowanie w wi�cej ni� jednym pluginie.
	 */
	namespace Other
	{

		/**
		 * Odczytuje ca�� zawarto�� z hPipe(zak�ada, �e jest mo�liwo�� odczytu).
		 * Gdy odczytane zostan� wszystkie dost�pne na dany moment dane, odczyt
		 * zostaje przerwany.
		 */
		PLUGIN_API std::string ReadFromPipe(HANDLE hPipe);

		/**
		 * Wywo�uje polecenie we wskazanym katalogu roboczym, podpinaj�c wewn�trzne
		 * \a {pipe}y pod standardowe wyj�cie i wyj�cie b��du. Czeka na zako�czenie
		 * procesu, dopiero po tym odczytuje wyj�cie procesu.
		 *
		 * \exception std::system_error Rzucane, gdy nie powiedzie si� uruchomienie
		 *		aplikacji lub utworzenie \a {pipe}.
		 */
		PLUGIN_API std::string CallSystemCommand(const std::string& command, const std::string& workingDirectory);

		/**
		 * Formatuje kod zwr�cony przez GetLastError jako ci�g znak�w UTF-8.
		 */
		PLUGIN_API std::string FormatError(DWORD code);

		/**
		 * Konwertuje ci�g znak�w w UCS-16 na UTF-8.
		 */
		PLUGIN_API std::string WideCharToUTF8(const wchar_t* str);

		/**
		 * Konwertuje ci�g znak�w w UTF-8 na UCS-16.
		 */
		PLUGIN_API std::shared_ptr<wchar_t> UTF8ToWideString(const std::string& str);

	}
}