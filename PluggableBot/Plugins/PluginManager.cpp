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
			char searchQuery[MAX_PATH * 2 + 1] = { 0 };

			GetFullPathNameA(this->pluginsPath.c_str(), MAX_PATH * 2, fullPath, nullptr);
			strcpy_s(searchQuery, fullPath);
			strcat_s(searchQuery, "\\*.dll");

			Logger->Information("Listing plugins in path '{0}'.", fullPath);
			WIN32_FIND_DATAA ffd;
			HANDLE hFind = FindFirstFileA(searchQuery, &ffd);

			if (hFind == INVALID_HANDLE_VALUE)
			{
				Logger->Error("Cannot list files in plugins directory! Error: {0}.", GetLastError());
				return;
			}

			do
			{
				this->LoadPlugin(fullPath, ffd.cFileName);
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
			this->plugins.clear();
			Logger->Information("All plugins unloaded.");
		}

		void PluginManager::LoadPlugin(const char* pluginsPath, const char* pluginName)
		{
			char fullPath[MAX_PATH * 2 + 1];
			strcpy_s(fullPath, pluginsPath);
			strcat_s(fullPath, "\\");
			strcat_s(fullPath, pluginName);

			Logger->Debug("Loading module {0} from path '{1}'.", pluginName, fullPath);
			HMODULE module = LoadLibrary(fullPath);
			if (module == nullptr)
			{
				Logger->Warning("Cannot load library {0}. Error: {1}.", pluginName, GetLastError());
				return;
			}

			CreatePluginMethod createMethod = (CreatePluginMethod)GetProcAddress(module, "CreatePlugin");
			DeletePluginMethod deleteMethod = (DeletePluginMethod)GetProcAddress(module, "DeletePlugin");

			if (createMethod == nullptr || deleteMethod == nullptr)
			{
				FreeLibrary(module);
				Logger->Warning("Module {0} does not have CreatePlugin/DeletePlugin methods!", pluginName);
				return;
			}

			IPlugin* plugin = createMethod(this->context);

			if (plugin == nullptr)
			{
				FreeLibrary(module);
				Logger->Warning("CreatePlugin of {0} did not return valid IPlugin object.", pluginName);
				return;
			}

			Logger->Information("Plugin {0} loaded.", plugin->GetName());
			this->plugins.push_back(std::make_tuple(plugin, module, deleteMethod));

			Logger->Debug("Configuring plugin.");
			plugin->Configure(this->configuration.get<jsonxx::Object>(plugin->GetName(), jsonxx::Object()));
		}

		std::vector<Commands::CommandPointer> PluginManager::GetCombinedCommands()
		{
			std::vector<Commands::CommandPointer> commands;
			for (auto p : this->plugins)
			{
				if (std::get<0>(p)->GetSupportedCommands() != nullptr)
				{
					commands.insert(commands.begin(),
						std::get<0>(p)->GetSupportedCommands()->begin(),
						std::get<0>(p)->GetSupportedCommands()->end());
				}
			}
			return commands;
		}

		std::vector<ProtocolPointer> PluginManager::GetCombinedProtocols()
		{
			std::vector<ProtocolPointer> protocols;
			for (auto p : this->plugins)
			{
				if (std::get<0>(p)->GetSupportedProtocols() != nullptr)
				{
					protocols.insert(protocols.begin(),
						std::get<0>(p)->GetSupportedProtocols()->begin(),
						std::get<0>(p)->GetSupportedProtocols()->end());
				}
			}
			return protocols;
		}
	}
}