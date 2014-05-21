#include <WinSock2.h>
#include "GGClient.h"

namespace PluggableBot
{
	namespace DefaultProtocols
	{

		char* Copy(const std::string& str)
		{
			char *buffer = new char[str.length() + 1];
			memcpy(buffer, str.c_str(), str.length() + 1);
			return buffer;
		}

		GGClient::GGClient(int uid, const std::string& password, int status, const std::string& statusDescription, int timeout)
			: timeout(timeout), session(nullptr)
		{
			memset(&this->loginParams, 0, sizeof(gg_login_params));
			this->loginParams.struct_size = sizeof(gg_login_params);
			this->loginParams.async = true;
			this->loginParams.encoding = GG_ENCODING_UTF8;

			this->loginParams.uin = uid;
			this->loginParams.password = Copy(password);

			this->loginParams.status = status;
			this->loginParams.status_descr = Copy(statusDescription);
		}


		GGClient::~GGClient()
		{
			this->Disconnect();

			delete[] this->loginParams.password;
			delete[] this->loginParams.status_descr;
			memset(&this->loginParams, 0, sizeof(gg_login_params));
		}

		void GGClient::Connect()
		{
			this->session = gg_login(&this->loginParams);
			if (!this->session)
			{
				throw ConnectionFailureException("Cannot create GG session.");
			}

			int loginTimeout = this->timeout * ConnectTimeoutMultiplier;

			int eventType;
			gg_event* event = nullptr;
			try
			{
				event = this->WaitForEvent(loginTimeout);
			}
			catch (...)
			{
				if (event != nullptr)
				{
					gg_free_event(event);
				}
				this->Disconnect();
				throw;
			}

			eventType = event != nullptr ? event->type : GG_EVENT_NONE;
			gg_free_event(event);

			switch (eventType)
			{
			case GG_EVENT_CONN_SUCCESS:
				if (gg_notify(this->session, nullptr, 0) == -1)
				{
					this->Disconnect();
					throw ConnectionFailureException("Cannot send the user list.");
				}
				break;

			case GG_EVENT_CONN_FAILED:
				this->Disconnect();
				throw ConnectionFailureException("Server rejected the connection.");

			case GG_EVENT_NONE:
				this->Disconnect();
				throw ConnectionFailureException("Connection timeout.");

			default:
				this->Disconnect();
				throw ConnectionFailureException("Server sent invalid message.");
			}
		}

		void GGClient::Disconnect()
		{
			if (this->session != nullptr)
			{
				gg_logoff(this->session);
				gg_free_session(this->session);
				this->session = nullptr;
			}
		}

		gg_event* GGClient::WaitForEvent(int timeout)
		{
			timeval tv = { timeout, 0 };

			FD_ZERO(&this->readSet);
			FD_ZERO(&this->writeSet);

			if (this->session->check & GG_CHECK_READ)
			{
				FD_SET(this->session->fd, &this->readSet);
			}
			if (this->session->check & GG_CHECK_WRITE)
			{
				FD_SET(this->session->fd, &this->writeSet);
			}

			int result = select(this->session->fd, &this->readSet, &this->writeSet, nullptr, &tv);

			if (result == -1)
			{
				throw ConnectionFailureException("Select failed.");
			}
			if (this->session->soft_timeout == 0 && this->session->timeout != -1 && this->session->timeout == 1)
			{
				throw ConnectionFailureException("libgadu detected timeout.");
			}

			gg_event* event;
			if (FD_ISSET(this->session->fd, &this->readSet) || FD_ISSET(this->session->fd, &this->writeSet) ||
				(this->session->timeout == 0 && this->session->soft_timeout))
			{
				if (!(event = gg_watch_fd(this->session)))
				{
					throw ConnectionFailureException("Cannot retrieve event from the library.");
				}
			}
			return nullptr;
		}
	}
}