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
		 * Wynik wykonywania komendy. Zawiera tre�� odpowiedzi i opcjonalny obiekt b�d�cy dodatkowymi danymi(JSON).
		 */
		class PLUGIN_API CommandExecutionResults
		{
		public:
			/**
			 * Okre�la, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			const bool IsAsync;

			/**
			 * Tre�� wiadomo�ci maj�cej by� odpowiedzi�.
			 */
			const std::string Message;

			/**
			 * Obiekt b�d�cy dodatkowymi danymi. Jest opcjonalny(mo�e by� nullptr).
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