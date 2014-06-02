#pragma once
#include "MessageReceived.h"
#include "SendMessage.h"
#include "ProtocolFailure.h"
#include "ShutdownRequest.h"
#include "AsyncExecutionFailure.h"

#define $MessageIs(msgClass) message->Type == msgClass::MessageType
#define $HandleMessage(msgClass) \
	if (message->Type == msgClass::MessageType) \
	{\
		this->Handle((msgClass*)message.get()); \
	}