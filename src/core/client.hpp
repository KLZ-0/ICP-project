/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <QPushButton>
#include <mqtt/async_client.h>
#include <mqtt/client.h>
#include <string>

#include "action_listener.hpp"

namespace Core
{
	class Client
	{
	public:
		Client() = delete;
		Client(const std::string &clientId);
		
	private:
		static constexpr std::string_view kServerUri = "tcp://test.mosquitto.org:1883";
		mqtt::async_client client_;
		mqtt::connect_options connOpts_;
		mqtt::iaction_listener_ptr actionListener_;
	};
} // namespace Core
