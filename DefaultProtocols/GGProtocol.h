#pragma once
#include <PluggableBot/ApplicationContext.h>
#include <PluggableBot/IProtocol.h>
#include <PluggableBot/External/jsonxx.h>
#include <thread>

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		/**
		 * Obs³uguje protokó³ GG.
		 */
		class GGProtocol
			: public IProtocol
		{
		public:
			GGProtocol(ApplicationContext* context, const jsonxx::Object& config);
			virtual ~GGProtocol();

			virtual void Start();
			virtual void Stop();

		private:
			ApplicationContext* const context;
			std::thread main;
		};

	}
}