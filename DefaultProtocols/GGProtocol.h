#pragma once
#include <PluggableBot/ApplicationContext.h>
#include <PluggableBot/IProtocol.h>
#include <PluggableBot/External/jsonxx.h>
#include <thread>

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
			bool Configure(const jsonxx::Object& config);
			virtual ~GGProtocol();

			virtual void Start();
			virtual void Stop();

			static ConfigurationStatus CheckConfiguration(const jsonxx::Object& config);

		private:
			ApplicationContext* const context;
			std::thread main;
		};

	}
}