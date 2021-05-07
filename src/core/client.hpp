/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <mqtt/async_client.h>
#include <qobject.h>
#include <string>

#include "action_listener.hpp"
#include "callback.hpp"

namespace Core
{
	class Client : public QObject
	{
		Q_OBJECT
	public:
		Client() = delete;
		Client(const std::string &clientId);

	public slots:
		void Connect();

		void Disconnect();

		void Subscribe(const QSet<QString> &topics);

		void Unsubscribe(const QSet<QString> &topics);

	signals:
		void Connected();

		void ConnectionLost(const QString cause);

		void MessageArrived(mqtt::const_message_ptr msg);

		void ServerUnreachable();

		void ActionSucceeded(const mqtt::token &tok);

		void ActionFailed(const mqtt::token &tok);

	private:
		static constexpr std::string_view kServerUri = "tcp://test.mosquitto.org:1883";
		mqtt::async_client client_;
		mqtt::connect_options connOpts_;
		ActionListener actionListener_;
		Callback callback_;
		static constexpr int kQos = 0;
	};
} // namespace Core
