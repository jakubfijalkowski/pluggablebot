#pragma once
#include <string>
#include <PluggableBot/UserData.h>
#include <PluggableBot/IProtocol.h>

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		/**
		 * Pobiera aktualną ścieżkę użytkownika.
		 */
		std::string GetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier);

		/**
		 * Zmienia aktualną ścieżkę użytkownika.
		 */
		void SetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier, const std::string& path);

		/**
		 * Sprowadza ścieżkę do "formy normalnej" Windowsa.
		 */
		std::string SanitizePath(const std::string& path);

		/**
		 * Łączy dwie ścieżki w jedną. Jeśli coś się nie powiedzie, zwrócony zostanie pusty string.
		 */
		std::string JoinPath(const std::string& path1, const std::string& path2);
	}
}
