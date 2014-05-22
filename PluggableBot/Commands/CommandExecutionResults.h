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
		 * Wynik wykonywania komendy. Zawiera treść odpowiedzi i opcjonalny obiekt będący dodatkowymi danymi(JSON).
		 */
		class PLUGIN_API CommandExecutionResults
		{
		public:
			/**
			 * Określa, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			const bool IsAsync;

			/**
			 * Treść wiadomości mającej być odpowiedzią.
			 */
			const std::string Message;

			/**
			 * Obiekt będący dodatkowymi danymi. Jest opcjonalny(może być nullptr).
			 */
			const std::shared_ptr<const jsonxx::Object> AdditionalData;

			/**
			 * Inicjalizuje obiekt.
			 */
			CommandExecutionResults(const std::string& message, bool isAsync = false, std::shared_ptr<const jsonxx::Object> additionalData = nullptr)
				: IsAsync(isAsync), Message(message), AdditionalData(additionalData)
			{ }

			/**
			 * Inicjalizuje obiekt pustej wiadomości
			 */
			CommandExecutionResults(bool isAsync = false)
				: IsAsync(isAsync), Message(), AdditionalData()
			{ }
		};

	}
}