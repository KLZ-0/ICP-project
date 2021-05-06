/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <mqtt/async_client.h>
#include <string>

#include "action_listener.hpp"
#include "callback.hpp"

namespace Core
{
	template<class CB = Callback, class AL = ActionListener>
	class Client
	{
	public:
		Client() = delete;
		Client(const std::string &clientId)
			: client_(kServerUri.data(), clientId),
			  callback_(client_) {
			connOpts_.set_clean_session(false);
			connOpts_.set_keep_alive_interval(20);
		}

	private:
		static constexpr std::string_view kServerUri = "tcp://test.mosquitto.org:1883";
		mqtt::async_client client_;
		mqtt::connect_options connOpts_;
		AL actionListener_;
		CB callback_;
	};
} // namespace Core
