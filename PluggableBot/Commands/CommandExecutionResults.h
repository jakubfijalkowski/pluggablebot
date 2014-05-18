#pragma once
#include <string>
#include <memory>
#include "../Config.h"
#include "../External/jsonxx.h"

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Wynik wykonywania komendy. Zawiera treœæ odpowiedzi i opcjonalny obiekt bêd¹cy dodatkowymi danymi(JSON).
		 */
		class PLUGIN_API CommandExecutionResults
		{
		public:
			/**
			 * Okreœla, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			const bool IsAsync;

			/**
			 * Treœæ wiadomoœci maj¹cej byæ odpowiedzi¹.
			 */
			const std::string Message;

			/**
			 * Obiekt bêd¹cy dodatkowymi danymi. Jest opcjonalny(mo¿e byæ nullptr).
			 */
			const std::shared_ptr<const jsonxx::Object> AdditionalData;

			/**
			 * Inicjalizuje obiekt.
			 */
			CommandExecutionResults(const std::string& message, bool isAsync = false, std::shared_ptr<const jsonxx::Object> additionalData = nullptr)
				: IsAsync(isAsync), Message(message), AdditionalData(additionalData)
			{ }
		};

	}
}