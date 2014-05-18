#include <Windows.h>
#include "PluginManager.h"

namespace PluggableBot
{
	namespace Plugins
	{
		static const char* DefaultPluginsPath = "Plugins";

		PluginManager::PluginManager(ApplicationContext* context)
			: Logger(Logging::LogFactory::GetLogger("PluginManager")), context(context)
		{ }

		PluginManager::~PluginManager()
		{
			if (!this->plugins.empty())
			{
				this->Unload();
			}
		}

		void PluginManager::Configure(const jsonxx::Object& config)
		{
			this->configuration.import(config);

			this->pluginsPath = this->configuration.get<std::string>("pluginsPath", DefaultPluginsPath);
			Logger->Information("Plugin manager configured with path '{0}'.", this->pluginsPath);
		}

		void PluginManager::Load()
		{
			Logger->Debug("Loading plugins.");

			char fullPath[MAX_PATH * 2 + 1] = { 0 };
			DWORD length = GetFullPathNameA(this->pluginsPath.c_str(), MAX_PATH * 2, fullPath, nullptr);
			Logger->Information("Listing plugins in path '{0}'.", fullPath);

			strcat_s(fullPath, "\\*.dll");

			WIN32_FIND_DATAA ffd;
			HANDLE hFind = FindFirstFileA(fullPath, &ffd);

			if (hFind == INVALID_HANDLE_VALUE)
			{
				Logger->Error("Cannot list files in plugins directory! Error: {0}.", GetLastError());
				return;
			}

			do
			{
				this->LoadPlugin(ffd.cFileName);
			} while (FindNextFile(hFind, &ffd));

			DWORD lastError = GetLastError();
			if (lastError != ERROR_NO_MORE_FILES)
			{
				Logger->Warning("FindNextFile failed. Error: {0}.", lastError);
			}
			else
			{
				FindClose(hFind);
			}

			Logger->Information("{0} plugins loaded.", this->plugins.size());
		}

		void PluginManager::Unload()
		{
			Logger->Debug("Unloading plugins.");
			for (auto t : this->plugins)
			{
				std::get<2>(t)(std::get<0>(t));
				FreeLibrary(std::get<1>(t));
			}
			Logger->Information("All plugins unloaded.");
		}

		void PluginManager::LoadPlugin(const char* path)
		{
			HMODULE module = LoadLibrary(path);
			if (module == nullptr)
			{
				Logger->Warning("Cannot load library {0}. Error: {1}.", path, GetLastError());
				return;
			}

			CreatePluginMethod createMethod = (CreatePluginMethod)GetProcAddress(module, "CreatePlugin");
			DeletePluginMethod deleteMethod = (DeletePluginMethod)GetProcAddress(module, "DeletePlugin");

			if (createMethod == nullptr || deleteMethod == nullptr)
			{
				Logger->Warning("Module {0} does not have CreatePlugin/DeletePlugin methods!", path);
				return;
			}

			IPlugin* plugin = createMethod(this->context);

			if (plugin == nullptr)
			{
				Logger->Warning("CreatePlugin of {0} did not return valid IPlugin object.", path);
				return;
			}

			Logger->Information("Plugin {0} loaded.", plugin->GetName());
			this->plugins.push_back(std::make_tuple(plugin, module, deleteMethod));

			Logger->Debug("Configuring plugin.");
			plugin->Configure(this->configuration.get<jsonxx::Object>(plugin->GetName()));
		}

	}
}