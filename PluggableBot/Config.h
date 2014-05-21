#pragma once

// Kilka makr ułatwiających budowę DLL-ki

#ifdef PLUGIN_DLL
#define PLUGIN_API __declspec(dllimport)
#else
#define PLUGIN_API __declspec(dllexport)
#endif

#pragma warning(disable : 4251)