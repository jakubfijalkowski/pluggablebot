#include "UserData.h"

namespace PluggableBot
{
	class IProtocol;

	UserDataMap::UserDataMap()
		: lastAccessTime(time(nullptr))
	{ }

	bool UserDataMap::Has(const std::string& key)
	{
		return this->UpdateAccess() && this->data.find(key) != this->data.end();
	}

	const std::string& UserDataMap::operator[](const std::string& key)
	{
		this->UpdateAccess();
		return this->data[key];
	}

	void UserDataMap::Set(const std::string& key, const std::string& value)
	{
		this->lastAccessTime = time(nullptr);
		this->data[key] = value;
	}

	bool UserDataMap::UpdateAccess()
	{
		time_t currTime = time(nullptr);
		if (difftime(currTime, this->lastAccessTime) > UserData::RetentionTime)
		{
			this->data.clear();
			this->lastAccessTime = currTime;
			return false;
		}
		this->lastAccessTime = currTime;
		return true;
	}

	UserDataMap& UserData::Get(const IProtocol* protocol, const std::string& identifier)
	{
		UserKey key = UserKey::pair(protocol, identifier);
		return this->data[key];
	}

	size_t UserData::UserKeyHash::operator()(const UserData::UserKey& key)
	{
		size_t hash = 17;
		hash = hash * 23 + (size_t)key.first;
		hash = hash * 23 + std::hash<std::string>()(key.second);
		return hash;
	}

}