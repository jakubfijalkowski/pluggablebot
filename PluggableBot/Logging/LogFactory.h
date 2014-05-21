#pragma once
#include <string>
#include <vector>
#include "../Config.h"
#include "Logger.h"
#include "IOutput.h"

namespace PluggableBot
{
	namespace Logging
	{
		
		/**
		 * Fabryka dla nazwanych obiektów Logger. Zaimplementowane jako klasa statyczna.
		 *
		 * W aktualnej formie nie ma możliwości konfiguracji biblioteki.
		 */
		class PLUGIN_API LogFactory
		{
		public:
			/**
			 * Pobiera Logger o wskazanej nazwie. Obiekt jest zarządzany w całości przez
			 * fabrykę i nie powinien być zwalniany.
			 *
			 * Jeśli logger o podanej nazwie już istnieje, zostaje zwrócowny. W przeciwnym razie
			 * zostaje utworzony nowy obiekt.
			 *
			 * \param name Nazwa loggera.
			 */
			static LoggerPointer GetLogger(const std::string& name);

			/**
			 * Dodaje wyjście, które będzie używane przez wszystkie nowe loggery. Wejście przekazywane jest na własność.
			 *
			 * \param output Wyjście.
			 */
			static void AddOutput(IOutput* output);

			/**
			 * Czyści pozostałości po loggerach.
			 * Ta metoda powinna zostać wywołana jako ostatnia w aplikacji!
			 */
			static void Unload();

		private:
			static std::vector<IOutput*> outputs;
		};

	}
}