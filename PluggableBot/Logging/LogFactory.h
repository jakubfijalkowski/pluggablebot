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
		 * Fabryka dla nazwanych obiekt�w Logger. Zaimplementowane jako klasa statyczna.
		 *
		 * W aktualnej formie nie ma mo�liwo�ci konfiguracji biblioteki.
		 */
		class LogFactory
		{
		public:
			/**
			 * Pobiera Logger o wskazanej nazwie. Obiekt jest zarz�dzany w ca�o�ci przez
			 * fabryk� i nie powinien by� zwalniany.
			 *
			 * Je�li logger o podanej nazwie ju� istnieje, zostaje zwr�cowny. W przeciwnym razie
			 * zostaje utworzony nowy obiekt.
			 *
			 * \param name Nazwa loggera.
			 */
			static LoggerPointer GetLogger(const std::string& name);

			/**
			 * Dodaje wyj�cie, kt�re b�dzie u�ywane przez wszystkie nowe loggery. Wej�cie przekazywane jest na w�asno��.
			 *
			 * \param output Wyj�cie.
			 */
			static void AddOutput(IOutput* output);

			/**
			 * Czy�ci pozosta�o�ci po loggerach.
			 * Ta metoda powinna zosta� wywo�ana jako ostatnia w aplikacji!
			 */
			static void Unload();

		private:
			static std::vector<IOutput*> outputs;
		};

	}
}