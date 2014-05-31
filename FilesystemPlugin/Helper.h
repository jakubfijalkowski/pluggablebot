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

	}
}
