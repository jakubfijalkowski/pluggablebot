#pragma once

// Kilka makr u³atwiaj¹cych budowê DLL-ki

#ifdef PLUGIN_DLL
#define PLUGIN_API __declspec(dllimport)
#else
#define PLUGIN_API __declspec(dllexport)
#endif

#pragma warning(disable : 4251)