#include "Messenger.h"

namespace PluggableBot
{
	namespace Messaging
	{

		Messenger::Messenger()
			: waitCount(0)
		{
			InitializeCriticalSection(&this->lock);
			this->newMessageEvent = CreateEvent(nullptr, TRUE, FALSE, TEXT("NewMessage"));
		}

		Messenger::~Messenger()
		{
			CloseHandle(this->newMessageEvent);
			DeleteCriticalSection(&this->lock);
		}

		void Messenger::Send(MessagePointer message)
		{
			EnterCriticalSection(&this->lock);
			this->messages.push_back(message);
			LeaveCriticalSection(&this->lock);

			if (this->waitCount > 0)
			{
				SetEvent(this->newMessageEvent);
			}
		}

		MessagePointer Messenger::Get(int type, DWORD timeout)
		{
			EnterCriticalSection(&this->lock);

			MessagePointer msg;

			for (auto it = this->messages.begin(); it != this->messages.end(); ++it)
			{
				if ((*it)->Type == type)
				{
					msg = *it;
					this->messages.erase(it);
					break;
				}
			}

			LeaveCriticalSection(&this->lock);

			if (msg == nullptr && this->WaitForNewObject(timeout))
			{
				return this->Get(type, timeout);
			}
			return msg;
		}

		MessageListPointer Messenger::Get(MessagePredicate predicate, DWORD timeout)
		{
			MessageListPointer msgs(new MessageList());
			this->Get(predicate, timeout, msgs);
			return msgs;
		}

		void Messenger::Get(MessagePredicate predicate, DWORD timeout, MessageListPointer output)
		{
			EnterCriticalSection(&this->lock);

			for (int i = this->messages.size() - 1; i >= 0; i--)
			{
				if (predicate(this->messages[i].get()))
				{
					output->push_back(this->messages[i]);
					this->messages.erase(this->messages.begin() + i);
				}
			}

			LeaveCriticalSection(&this->lock);

			if (output->size() == 0 && this->WaitForNewObject(timeout))
			{
				this->Get(predicate, timeout, output);
			}
		}

		bool Messenger::WaitForNewObject(DWORD timeout)
		{
			InterlockedIncrement(&this->waitCount);
			auto result = WaitForSingleObject(this->newMessageEvent, timeout);

			if (InterlockedDecrement(&this->waitCount) == 0)
			{
				ResetEvent(this->newMessageEvent);
			}
			return result == WAIT_OBJECT_0;
		}
	}
}