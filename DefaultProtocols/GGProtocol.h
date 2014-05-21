#pragma once
#include <PluggableBot/ApplicationContext.h>
#include <PluggableBot/IProtocol.h>
#include <PluggableBot/Logging/LogFactory.h>
#include <PluggableBot/External/jsonxx.h>
#include <thread>
#include <memory>
#include "GGClient.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		enum class ConfigurationStatus
		{
			Valid,
			Invalid,
			Disabled
		};

		/**
		 * Obs³uguje protokó³ GG.
		 */
		class GGProtocol
			: public IProtocol
		{
		public:
			GGProtocol(ApplicationContext* context, const jsonxx::Object& config);

			virtual void Start();
			virtual void Stop();

			static ConfigurationStatus CheckConfiguration(const jsonxx::Object& config);

		private:
			bool TryConnect();

			const Logging::LoggerPointer Logger;

			const int MaxRetryCount;

			ApplicationContext* const context;
			std::thread main;

			std::unique_ptr<GGClient> client;
		};

	}
}