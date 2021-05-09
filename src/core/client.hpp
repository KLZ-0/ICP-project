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
	/**
	 * @class Client
	 * @brief Implements a client for connecting to and communicating with and mqtt server
	 */
	class Client : public QObject
	{
		Q_OBJECT
	public:
		Client() = delete;
		/**
		 * @brief Client Constructor
		 * @param clientId
		*/
		Client(const std::string &clientId);

	public slots:
		/**
		 * @brief	Connects to the default mqtt server: tcp://test.mosquitto.org:1883
		*/
		void Connect();
		/**
		 * @brief Disconnect from the server
		*/
		void Disconnect();
		/**
		 * @brief Subscirbe to a set of topics on the currently connected server
		 * @param topics 
		*/
		void Subscribe(const QSet<QString> &topics);
		/**
		 * @brief Unsubscribe a set of topics from the currently connected server
		 * @param topics 
		*/
		void Unsubscribe(const QSet<QString> &topics);
		/**
		 * @brief Publish a mqtt message to the currently connected server
		 * @param msg 
		*/
		void Publish(mqtt::const_message_ptr msg);

	signals:
		/**
		 * @brief Qt signal when we successfully connect to a server
		*/
		void Connected();
		/**
		 * @brief Qt signal when we loose connection from a server
		 * @param cause 
		*/
		void ConnectionLost(const QString &cause);
		/**
		 * @brief Qt signal for incoming messages
		 * @param msg 
		*/
		void MessageArrived(mqtt::const_message_ptr msg);
		/**
		 * @brief Qt signal when we we failed to (re)connect after 5 automatic tries
		*/
		void ServerUnreachable();
		/**
		 * @brief Qt signal for a successful mqtt action - info in token
		 * @param tok 
		*/
		void ActionSucceeded(const mqtt::token &tok);
		/**
		 * @brief Qt for a failed mqtt action - info in token
		 * @param tok 
		*/
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
