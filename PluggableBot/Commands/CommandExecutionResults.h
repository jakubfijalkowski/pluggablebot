#pragma once
#include <string>
#include <memory>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Wynik wykonywania komendy. Zawiera treœæ odpowiedzi i opcjonalny obiekt bêd¹cy dodatkowymi danymi(JSON).
		 */
		class CommandExecutionResults
		{
		public:
			/**
			 * Okreœla, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			const bool IsAsync;

			/**
			 * Treœæ wiadomoœci maj¹cej byæ odpowiedzi¹.
			 */
			const std::wstring Message;

			/**
			 * Obiekt bêd¹cy dodatkowymi danymi. Jest opcjonalny(mo¿e byæ nullptr).
			 */
			// TODO: zmieniæ typ na w³aœciwy
			const void* const AdditionalData;

			/**
			 * Inicjalizuje obiekt.
			 */
			CommandExecutionResults(const std::wstring& message, bool isAsync = false, void* additionalData = nullptr)
				: IsAsync(isAsync), Message(message), AdditionalData(additionalData)
			{ }
		};

	}
}