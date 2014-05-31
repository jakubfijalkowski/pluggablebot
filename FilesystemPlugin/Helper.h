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
	}
}
