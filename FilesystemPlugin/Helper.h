#pragma once
#include <string>
#include <PluggableBot/UserData.h>
#include <PluggableBot/IProtocol.h>

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		/**
		 * Pobiera aktualn� �cie�k� u�ytkownika.
		 */
		std::string GetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier);

		/**
		 * Zmienia aktualn� �cie�k� u�ytkownika.
		 */
		void SetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier, const std::string& path);

		/**
		 * Sprowadza �cie�k� do "formy normalnej" Windowsa.
		 */
		std::string SanitizePath(const std::string& path);

		/**
		 * ��czy dwie �cie�ki w jedn�. Je�li co� si� nie powiedzie, zwr�cony zostanie pusty string.
		 */
		std::string JoinPath(const std::string& path1, const std::string& path2);
	}
}
