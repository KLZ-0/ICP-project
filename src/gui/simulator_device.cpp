/**
 * @author Kevin Lackó (xlacko08)
 */

#include "simulator_device.hpp"

#include <qjsonarray.h>
#include <qjsonobject.h>

SimulatorDevice::SimulatorDevice(Core::Client &client, const QJsonObject &deviceConfigJson)
	: client(client) {
	setDeviceConfigfromJson(deviceConfigJson);
	init();
}

SimulatorDevice::SimulatorDevice(Core::Client &client, DeviceConfig config)
	: client(client), config(config) {
	init();
}

void SimulatorDevice::start() {
	if (config.deviceType == "publisher") {
		startPublisher();
	} else {
		startReceiver();
	}
}

void SimulatorDevice::stop() {
	if (config.deviceType == "publisher") {
		stopPublisher();
	} else {
		stopReceiver();
	}
}

QJsonObject SimulatorDevice::toJson() const {
	return deviceConfigToJson(config);
}

void SimulatorDevice::setDeviceConfigfromJson(const QJsonObject &deviceConfigJson) {
	const QJsonObject &json = deviceConfigJson;
	config.topic = json["topic"].toString();
	if (config.topic.isEmpty()) {
		valid = false;
	}
	config.deviceType = json["deviceType"].toString();

	if (config.deviceType == "publisher") {
		config.publisher.interval_ms = json["interval_ms"].toInt();
		config.publisher.dataType = json["dataType"].toString();

		if (config.publisher.dataType == "string") {
			QJsonArray dataArray = json["data"].toArray();
			for (const auto &value : dataArray) {
				config.publisher.data.append(value.toString());
			}
		} else if (config.publisher.dataType == "binary") {
			config.publisher.filePath = json["filePath"].toString();
		} else {
			valid = false;
		}

	} else if (config.deviceType == "receiver") {
		config.receiver.targetTopic = json["targetTopic"].toString();
		config.receiver.delay_ms = json["delay_ms"].toInt();
	} else {
		valid = false;
	}
}

bool SimulatorDevice::isValid() const {
	return valid;
}

QJsonObject SimulatorDevice::deviceConfigToJson(const DeviceConfig &config) {
	QJsonObject deviceJson;
	deviceJson.insert("topic", config.topic);
	deviceJson.insert("deviceType", config.deviceType);

	if (config.deviceType == "publisher") {
		deviceJson.insert("interval_ms", config.publisher.interval_ms);
		deviceJson.insert("dataType", config.publisher.dataType);

		if (config.publisher.dataType == "string") {
			deviceJson.insert("randomData", config.publisher.randomData);

			QJsonArray dataArray;
			for (const auto &str : config.publisher.data) {
				dataArray.append(str);
			}
			deviceJson.insert("data", dataArray);

		} else /* "binary" */ {
			deviceJson.insert("filePath", config.publisher.filePath);
		}

	} else /* "receiver" */ {
		deviceJson.insert("targetTopic", config.receiver.targetTopic);
		deviceJson.insert("delay_ms", config.receiver.delay_ms);
	}

	return deviceJson;
}

void SimulatorDevice::init() {
	if (config.deviceType == "receiver") {
		client.Subscribe({config.topic});
	} else /* publisher */ {
	}
}

void SimulatorDevice::startReceiver() {
	recvConnection = connect(&client, &Core::Client::MessageArrived, this, &SimulatorDevice::receiveMessage);
}

void SimulatorDevice::stopReceiver() {
	disconnect(recvConnection);
}

void SimulatorDevice::startPublisher() {
	// todo: start publisher
}

void SimulatorDevice::stopPublisher() {
	// todo: stop publisher
}

void SimulatorDevice::receiveMessage(mqtt::const_message_ptr message) {
	QTimer::singleShot(config.receiver.delay_ms, [message, this]() {
		mqtt::message_ptr_builder builder;
		builder.topic(config.receiver.targetTopic.toStdString());
		builder.payload(message->get_payload());
		this->client.Publish(builder.finalize());
		qDebug() << "simulator device: msg forwarded from" << config.topic << "to" << config.receiver.targetTopic;
	});
}
