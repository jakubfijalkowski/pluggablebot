#pragma once
#include <string>
#include <PluggableBot/UserData.h>
#include <PluggableBot/IProtocol.h>

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		/**
		 * \brief Pobiera aktualną ścieżkę użytkownika. Ustawia domyślną, gdy użytkownik nie wskazał inaczej.
		 */
		std::string GetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier);

		/**
		 * \brief Zmienia aktualną ścieżkę użytkownika.
		 */
		void SetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier, const std::string& path);

		/**
		 * \brief Sprowadza ścieżkę do "formy normalnej" Windowsa.
		 *
		 * Przez "formę normalną" rozumiemy brak znaków * / * - zostaną one zamienione
		 * na znaki *\*.
		 */
		std::string SanitizePath(const std::string& path);

		/**
		 * \brief Łączy dwie ścieżki w jedną. Jeśli coś się nie powiedzie, zwrócony zostanie pusty string.
		 */
		std::string JoinPath(const std::string& path1, const std::string& path2);
	}
}
