#pragma once
#include <string>
#include <memory>

namespace PluggableBot
{
	namespace Commands
	{

		/**
		 * Wynik wykonywania komendy. Zawiera tre�� odpowiedzi i opcjonalny obiekt b�d�cy dodatkowymi danymi(JSON).
		 */
		class CommandExecutionResults
		{
		public:
			/**
			 * Okre�la, czy wynik komendy jest synchroniczny, czy asynchroniczny.
			 */
			const bool IsAsync;

			/**
			 * Tre�� wiadomo�ci maj�cej by� odpowiedzi�.
			 */
			const std::wstring Message;

			/**
			 * Obiekt b�d�cy dodatkowymi danymi. Jest opcjonalny(mo�e by� nullptr).
			 */
			// TODO: zmieni� typ na w�a�ciwy
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