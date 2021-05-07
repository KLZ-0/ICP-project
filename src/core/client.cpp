/**
 * @author Kevin Lackó (xlacko08)
 */
#include "client.hpp"
#include <qset.h>
#include <algorithm>

namespace Core
{
	Client::Client(const std::string &clientId)
		: client_(kServerUri.data(), clientId),
		  actionListener_(this),
		  callback_(this, client_) {
		connOpts_.set_clean_session(false);
		connOpts_.set_keep_alive_interval(20);
		client_.set_callback(callback_);
	}
	void Client::Connect() {
		try {
			std::cout << "Connecting to the MQTT server...\n"
					  << std::flush;
			client_.connect(connOpts_, nullptr, callback_);
		} catch (const mqtt::exception &exc) {
			std::cerr << "ERROR: Unable to connect to MQTT server: '"
					  << kServerUri.data() << "'" << exc << std::endl;
			emit ServerUnreachable();
		}
	}
	void Client::Subscribe(const QSet<QString> &topics) {
		mqtt::string_collection_ptr topicFilters = std::make_shared<mqtt::string_collection>();
		mqtt::iasync_client::qos_collection qos;
		std::for_each(topics.begin(), topics.end(), [&topicFilters,&qos](const QString &tf) {
			topicFilters->push_back(tf.toStdString());
			qos.push_back(kQos);
		});
		client_.subscribe(topicFilters, qos, nullptr, actionListener_);
	}
	void Client::Unsubscribe(const QSet<QString> &topics) {
		mqtt::string_collection_ptr topicFilters = std::make_shared<mqtt::string_collection>();
		mqtt::iasync_client::qos_collection qos;
		std::for_each(topics.begin(), topics.end(), [&topicFilters, &qos](const QString &tf) {
			topicFilters->push_back(tf.toStdString());
			qos.push_back(kQos);
		});
		client_.unsubscribe(topicFilters);
	}
} // namespace Core
