#pragma once
#include <string>
#include "ILogger.h"

namespace PluggableBot
{
	namespace Logging
	{
		
		/**
		 * Fabryka dla nazwanych obiekt�w ILogger. Zaimplementowane jako klasa statyczna.
		 *
		 * W aktualnej formie nie ma mo�liwo�ci konfiguracji biblioteki.
		 */
		class LogFactory
		{
		public:
			/**
			 * Pobiera ILogger o wskazanej nazwie. Obiekt jest zarz�dzany w ca�o�ci przez
			 * fabryk� i nie powinien by� zwalniany.
			 *
			 * Je�li logger o podanej nazwie ju� istnieje, zostaje zwr�cowny. W przeciwnym razie
			 * zostaje utworzony nowy obiekt.
			 *
			 * \param name Nazwa loggera.
			 */
			static ILogger* GetLogger(const std::string& name);

			/**
			 * Usuwa wszystkie instancje logger�w.
			 */
			static void Unload();
		};

	}
}