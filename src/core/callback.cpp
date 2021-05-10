/**
 * @author Kevin Lackó (xlacko08)
 */


#include "callback.hpp"

#include <mqtt/async_client.h>
#include <qdebug.h>

#include "client.hpp"

namespace Core
{
	Callback::Callback(Client *caller, mqtt::async_client &client)
		: sig_(caller), client_(client) {
	}
	void Callback::on_failure(const mqtt::token &asyncActionToken) {
		qDebug() << sig_->clientId.c_str() << "- connection attempt failed";
		if (++nRetry_ > kRetryLimit) {
			qDebug() << sig_->clientId.c_str() << "- server not available";
			emit sig_->ServerUnreachable();
		}
		client_.reconnect();
	}
	void Callback::on_success(const mqtt::token &asyncActionToken) {
		// same as Callback::connected
	}
	void Callback::connected(const std::string &cause) {
		qDebug() << sig_->clientId.c_str() << "- connected\tcause: " << cause.c_str();
		emit sig_->Connected();
	}
	void Callback::connection_lost(const std::string &cause) {
		qDebug() << sig_->clientId.c_str() << "- connection lost";
		emit sig_->ConnectionLost(cause.c_str());
		if (!cause.empty()) {
			qDebug() << "\tcause: " << cause.c_str();
		}
		qDebug() << sig_->clientId.c_str() << "- reconnecting...";
		nRetry_ = 0;
		client_.reconnect();
	}
	void Callback::message_arrived(mqtt::const_message_ptr msg) {
		qDebug() << sig_->clientId.c_str() << "- message arrived";
		emit sig_->MessageArrived(msg);
	}
	void Callback::delivery_complete(mqtt::delivery_token_ptr tok) {
		qDebug() << sig_->clientId.c_str() << "- delivery complete";
	}
} // namespace Core
