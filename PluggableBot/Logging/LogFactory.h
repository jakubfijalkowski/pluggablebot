#pragma once
#include <string>
#include <vector>
#include "Logger.h"
#include "IOutput.h"

namespace PluggableBot
{
	namespace Logging
	{
		
		/**
		 * Fabryka dla nazwanych obiektów Logger. Zaimplementowane jako klasa statyczna.
		 *
		 * W aktualnej formie nie ma mo¿liwoœci konfiguracji biblioteki.
		 */
		class LogFactory
		{
		public:
			/**
			 * Pobiera Logger o wskazanej nazwie. Obiekt jest zarz¹dzany w ca³oœci przez
			 * fabrykê i nie powinien byæ zwalniany.
			 *
			 * Jeœli logger o podanej nazwie ju¿ istnieje, zostaje zwrócowny. W przeciwnym razie
			 * zostaje utworzony nowy obiekt.
			 *
			 * \param name Nazwa loggera.
			 */
			static LoggerPointer GetLogger(const std::string& name);

			/**
			 * Dodaje wyjœcie, które bêdzie u¿ywane przez wszystkie nowe loggery. Wejœcie przekazywane jest na w³asnoœæ.
			 *
			 * \param output Wyjœcie.
			 */
			static void AddOutput(IOutput* output);

			/**
			 * Czyœci pozosta³oœci po loggerach.
			 * Ta metoda powinna zostaæ wywo³ana jako ostatnia w aplikacji!
			 */
			static void Unload();

		private:
			static std::vector<IOutput*> outputs;
		};

	}
}