#include <WinSock2.h>
#include <ctime>
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
			: timeout(timeout), session(nullptr), lastPingTime(0), pongReceived(true)
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

		void GGClient::Connect(const ContactList& contacts)
		{
			this->session = gg_login(&this->loginParams);
			if (!this->session)
			{
				throw ConnectionFailureException("Cannot create GG session.");
			}

			int loginTimeout = this->timeout * ConnectTimeoutMultiplier;

			int eventType = GG_EVENT_NONE;
			time_t startTime = time(nullptr);
			while (eventType != GG_EVENT_CONN_SUCCESS && difftime(time(nullptr), startTime) < loginTimeout)
			{
				std::shared_ptr<gg_event> event = nullptr;
				try
				{
					event = this->WaitForEvent(loginTimeout);
				}
				catch (...)
				{
					this->Disconnect();
					throw;
				}

				eventType = event != nullptr ? event->type : GG_EVENT_NONE;

				switch (eventType)
				{
				case GG_EVENT_CONN_SUCCESS:
					this->lastPingTime = time(nullptr);
					if (gg_notify(this->session, (uin_t*)contacts.data(), contacts.size()) == -1)
					{
						this->Disconnect();
						throw ConnectionFailureException("Cannot send the user list.");
					}
					return;

				case GG_EVENT_CONN_FAILED:
					this->Disconnect();
					throw ConnectionFailureException("Server rejected the connection.");
				}
			}
			throw ConnectionFailureException("Connection timed out.");
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

		GGEvent GGClient::HandleEvents()
		{
			time_t currTime = time(nullptr);
			if (difftime(currTime, this->lastPingTime) > PingTime)
			{
				if (!this->pongReceived)
				{
					throw ConnectionFailureException("Server did not send the pong response.");
				}
				gg_ping(this->session);
				this->lastPingTime = currTime;
			}

			auto event = this->WaitForEvent(this->timeout);

			if (event != nullptr)
			{
				if (event->type == GG_EVENT_PONG || event->type == GG_EVENT_PONG110)
				{
					this->pongReceived = true;
					return nullptr;
				}
				else if(event->type == GG_EVENT_DISCONNECT)
				{
					throw ConnectionFailureException("Server closed the connection.");
				}
			}

			return event;
		}

		void GGClient::SendMessage(uin_t receipent, const std::string& content)
		{
			gg_send_message(this->session, GG_CLASS_MSG | GG_CLASS_ACK, receipent, (const unsigned char*)content.c_str());
		}

		void GGClient::RequestImage(uin_t sender, uint32_t size, uint32_t crc32)
		{
			gg_image_request(this->session, sender, size, crc32);
		}

		GGEvent GGClient::WaitForEvent(int timeout)
		{
			timeval tv = { 0, timeout * 1000 };

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
				return std::shared_ptr<gg_event>(event, gg_free_event);
			}
			return nullptr;
		}
	}
}