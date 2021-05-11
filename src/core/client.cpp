/**
 * @file
 * @author Kevin Lackó (xlacko08)
 */
#include "client.hpp"

#include <algorithm>
#include <qdebug.h>
#include <qset.h>
#include <quuid.h>

namespace Core
{
	Client::Client(const std::string &clientId)
		: client_(kServerUri.data(), clientId + "_" + QUuid::createUuid().toString().toStdString()),
		  actionListener_(this),
		  callback_(this, client_),
		  clientId(clientId) {
		connOpts_.set_clean_session(true);
		connOpts_.set_keep_alive_interval(20);
		client_.set_callback(callback_);
	}
	void Client::Connect() {
		try {
			qDebug() << clientId.c_str() << "- connecting to the MQTT server...\n";
			client_.connect(connOpts_, nullptr, callback_);
		} catch (const mqtt::exception &exc) {
			qDebug() << "ERROR: " << clientId.c_str() << "- unable to connect to MQTT server: '"
					 << kServerUri.data() << "'" << exc.what();
			emit ServerUnreachable();
		}
	}
	void Client::Connect(const std::string_view &serverUri) {
		auto serverURIs = std::make_shared<mqtt::string_collection>();
		serverURIs->push_back(serverUri.data());
		connOpts_.set_servers(serverURIs);
		try {
			qDebug() << clientId.c_str() << "- connecting to the MQTT server...\n";
			client_.connect(connOpts_, nullptr, callback_);
		} catch (const mqtt::exception &exc) {
			qDebug() << "ERROR: " << clientId.c_str() << "- unable to connect to MQTT server: '"
					 << kServerUri.data() << "'" << exc.what();
			emit ServerUnreachable();
		}
	}
	void Client::Disconnect() {
		try {
			qDebug() << clientId.c_str() << "- disconnecting from the chat server...";
			client_.disconnect(nullptr, actionListener_)->wait();
			qDebug() << clientId.c_str() << "- OK";
		} catch (const mqtt::exception &exc) {
			qDebug() << "disconnect failed: " << exc.what();
		}
	}
	void Client::Subscribe(const QSet<QString> &topics) {
		if (topics.isEmpty()) {
			return;
		}
		mqtt::string_collection_ptr topicFilters = std::make_shared<mqtt::string_collection>();
		mqtt::iasync_client::qos_collection qos;
		std::for_each(topics.begin(), topics.end(), [&topicFilters, &qos](const QString &tf) {
			topicFilters->push_back(tf.toStdString());
			qos.push_back(kQos);
		});
		try {
			client_.subscribe(topicFilters, qos, nullptr, actionListener_);
		} catch (const mqtt::exception &exc) {
			qDebug() << clientId.c_str() << "- subscribe failed: " << exc.what();
		}
	}
	void Client::Unsubscribe(const QSet<QString> &topics) {
		if (topics.isEmpty()) {
			return;
		}
		mqtt::string_collection_ptr topicFilters = std::make_shared<mqtt::string_collection>();
		mqtt::iasync_client::qos_collection qos;
		std::for_each(topics.begin(), topics.end(), [&topicFilters, &qos](const QString &tf) {
			topicFilters->push_back(tf.toStdString());
			qos.push_back(kQos);
		});
		try {
			client_.unsubscribe(topicFilters);
		} catch (const mqtt::exception &exc) {
			qDebug() << clientId.c_str() << "- unsubscribe failed: " << exc.what();
		}
	}
	void Client::Publish(mqtt::const_message_ptr msg) {
		try {
			client_.publish(msg);
		} catch (const mqtt::exception &exc) {
			qDebug() << clientId.c_str() << "- publish failed: " << exc.what();
		}
	}
} // namespace Core
