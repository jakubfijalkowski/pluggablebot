#pragma once
#include <string>
#include <PluggableBot/UserData.h>
#include <PluggableBot/IProtocol.h>

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		/**
		 * Pobiera aktualn¹ œcie¿kê u¿ytkownika.
		 */
		std::string GetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier);

		/**
		 * Zmienia aktualn¹ œcie¿kê u¿ytkownika.
		 */
		void SetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier, const std::string& path);

		/**
		 * Sprowadza œcie¿kê do "formy normalnej" Windowsa.
		 */
		std::string SanitizePath(const std::string& path);

		/**
		 * £¹czy dwie œcie¿ki w jedn¹. Jeœli coœ siê nie powiedzie, zwrócony zostanie pusty string.
		 */
		std::string JoinPath(const std::string& path1, const std::string& path2);
	}
}
