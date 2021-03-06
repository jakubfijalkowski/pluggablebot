#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <ctime>
#include "Config.h"

namespace PluggableBot
{
	class IProtocol;

	/**
	 * \brief Wrapper na std::unordered_map, zapewniający bardziej zwarty dostęp do danych.
	 */
	class PLUGIN_API UserDataMap
	{
	public:
		UserDataMap();

		/**
		 * \brief Sprawdza, czy mapa zawiera element o podanym kluczu.
		 */
		bool Has(const std::string& key);

		/**
		 * \brief Pobiera element o wskazanym kluczu.
		 */
		const std::string& operator[](const std::string& key);

		/**
		 * \brief Dodaje/zmienia element o podanym kluczu.
		 */
		void Set(const std::string& key, const std::string& value);

	private:
		bool UpdateAccess();

		std::unordered_map<std::string, std::string> data;
		time_t lastAccessTime;
	};

	/**
	 * \brief Klasa przechowująca dane użytkownika.
	 *
	 * Dane są przechwoywane przez określony czas. Oznacza to, że gdy użytkownik
	 * nie wywoła komendy odwołującej się do danych przez ten czas, jego dane przepadają.
	 * Przez dane użytkownika rozumie się pary klucz-wartość, gdzie zarówno klucz jak i wartość
	 * są ciągami znaków.
	 */
	class PLUGIN_API UserData
	{
	public:
		/**
		 * \brief Czas pamiętania danych, w sekundach.
		 */
		static const int RetentionTime = 15 * 60;

		/**
		 * \brief Pobiera mapę z danymi dla wskazanego użytkownika.
		 */
		UserDataMap& Get(const IProtocol* protocol, const std::string& identifier);

	private:
		typedef std::pair<const IProtocol* const, std::string> UserKey;
		class PLUGIN_API UserKeyHash
		{
		public:
			size_t operator()(const UserKey& key);
		};

		typedef std::unordered_map<UserKey, UserDataMap, UserKeyHash> DataContainer;

		DataContainer data;
	};

}