/**
 * @author Kevin Lackó (xlacko08)
 */


#include "Callback.hpp"

#include "utils.hpp"
#include <mqtt/async_client.h>

namespace Core
{
	Callback::Callback(mqtt::async_client &client)
		: client_(client) {
	}
	void Callback::on_failure(const mqtt::token &asyncActionToken) {
		LOG("Connection attempt failed\n");
		if (++nRetry_ > kRetryLimit) {
			LOG_ERR("Server not available\n");
			exit(1);
		}
	}
	void Callback::on_success(const mqtt::token &asyncActionToken) {
		// same as Callback::connected
	}
	void Callback::connected(const std::string &cause) {
		LOG("Callback::connected not implemented\n");
	}
	void Callback::connection_lost(const std::string &cause) {
		LOG("Connection lost\n");
		if (!cause.empty()) {
			LOG("\tcause: " << cause << "\n");
		}
		LOG("Reconnecting...");
		nRetry_ = 0;
		client_.reconnect();
	}
	void Callback::message_arrived(mqtt::const_message_ptr msg) {
		LOG("Callback::message_arrived not implemented\n");
	}
	void Callback::delivery_complete(mqtt::delivery_token_ptr tok) {
		LOG("LOG: delivery complete\n");
	}
} // namespace Core
