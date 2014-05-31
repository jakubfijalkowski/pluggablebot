#include "Helper.h"
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <algorithm>

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

		std::string SanitizePath(const std::string& path)
		{
			std::string p2 = path;
			std::replace(p2.begin(), p2.end(), '/', '\\');
			return p2;
		}

		std::string JoinPath(const std::string& path1, const std::string& path2)
		{
			std::string newPath;
			if (!PathIsRelativeA(path2.c_str()))
			{
				newPath = path2;
			}
			else
			{
				char buffer[MAX_PATH];
				if (PathCombineA(buffer, path1.c_str(), path2.c_str()) != nullptr)
				{
					if (PathIsDirectoryA(buffer))
					{
						PathAddBackslashA(buffer);
					}
					newPath = buffer;
				}
			}
			return newPath;
		}

	}
}
