#pragma once
#include "MessageReceived.h"
#include "SendMessage.h"
#include "ProtocolFailure.h"
#include "ShutdownRequest.h"
#include "AsyncExecutionFailure.h"
#include "ImageReceived.h"
#include "AsyncCommandExecuted.h"

namespace PluggableBot
{
	/**
	 * \brief Przestrzeń nazw zawierająca wszystkie wiadomości używane przez aplikację.
	 */
	namespace Messages
	{ }
}

/**
 * \brief Makro ułatwiające sprawdzenie typu wiadomości.
 */
#define $MessageIs(msgClass) message->Type == msgClass::MessageType

/**
 * \brief Makro używane przez klasę Application do obsługi niektórych wiadomości.
 */
#define $HandleMessage(msgClass) \
	if (message->Type == msgClass::MessageType) \
	{\
		this->Handle((msgClass*)message.get()); \
	}