#pragma once
#include <string>
#include "ILogger.h"

namespace PluggableBot
{
	namespace Logging
	{
		
		/**
		 * Fabryka dla nazwanych obiektów ILogger. Zaimplementowane jako klasa statyczna.
		 *
		 * W aktualnej formie nie ma mo¿liwoœci konfiguracji biblioteki.
		 */
		class LogFactory
		{
		public:
			/**
			 * Pobiera ILogger o wskazanej nazwie. Obiekt jest zarz¹dzany w ca³oœci przez
			 * fabrykê i nie powinien byæ zwalniany.
			 *
			 * Jeœli logger o podanej nazwie ju¿ istnieje, zostaje zwrócowny. W przeciwnym razie
			 * zostaje utworzony nowy obiekt.
			 *
			 * \param name Nazwa loggera.
			 */
			static ILogger* GetLogger(const std::string& name);

			/**
			 * Usuwa wszystkie instancje loggerów.
			 */
			static void Unload();
		};

	}
}