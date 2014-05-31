#include "Helper.h"
#include <Windows.h>
#include <ShlObj.h>

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		const std::string CurrentPathKey = "CurrentDirectory";

		std::string GetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier)
		{
			auto map = userData.Get(protocol, identifier);
			auto currDir = map[CurrentPathKey];
			if (currDir.empty())
			{
				char path[MAX_PATH];
				SHGetFolderPathA(nullptr, CSIDL_PROFILE, nullptr, 0, path);
				currDir = path;
				map.Set(CurrentPathKey, currDir);
			}
			return currDir;
		}

		void SetCurrentPath(UserData& userData, const ProtocolPointer protocol, const std::string& identifier, const std::string& path)
		{
			userData.Get(protocol, identifier).Set(CurrentPathKey, path);
		}

	}
}
