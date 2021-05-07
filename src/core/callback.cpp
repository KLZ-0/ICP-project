/**
 * @author Kevin Lackó (xlacko08)
 */


#include "Callback.hpp"

#include <mqtt/async_client.h>
#include <qdebug.h>

#include "client.hpp"

namespace Core
{
	Callback::Callback(Client *caller, mqtt::async_client &client)
		: sig_(caller), client_(client) {
	}
	void Callback::on_failure(const mqtt::token &asyncActionToken) {
		qDebug() << "Connection attempt failed";
		if (++nRetry_ > kRetryLimit) {
			qDebug() << "Server not available";
			emit sig_->ServerUnreachable();
		}
		client_.reconnect();
	}
	void Callback::on_success(const mqtt::token &asyncActionToken) {
		// same as Callback::connected
	}
	void Callback::connected(const std::string &cause) {
		qDebug() << "Connected\tcause: " << cause.c_str();
		emit sig_->Connected();
	}
	void Callback::connection_lost(const std::string &cause) {
		qDebug() << "Connection lost";
		emit sig_->ConnectionLost(cause.c_str());
		if (!cause.empty()) {
			qDebug() << "\tcause: " << cause.c_str();
		}
		qDebug() << "Reconnecting...";
		nRetry_ = 0;
		client_.reconnect();
	}
	void Callback::message_arrived(mqtt::const_message_ptr msg) {
		qDebug() << "Message arrived";
		emit sig_->MessageArrived(msg);
	}
	void Callback::delivery_complete(mqtt::delivery_token_ptr tok) {
		qDebug() << "delivery complete";
	}
} // namespace Core
