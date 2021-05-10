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

SimulatorDevice::SimulatorDevice(Core::Client &client, DeviceConfig deviceConfig)
	: client(client), deviceConfig(deviceConfig) {
	init();
}

void SimulatorDevice::start() {
	if (deviceConfig.deviceType == "publisher") {
		startPublisher();
	} else {
		startReceiver();
	}
}

void SimulatorDevice::stop() {
	if (deviceConfig.deviceType == "publisher") {
		stopPublisher();
	} else {
		stopReceiver();
	}
}

QJsonObject SimulatorDevice::toJson() const {
	return deviceConfigToJson(deviceConfig);
}

void SimulatorDevice::setDeviceConfigfromJson(const QJsonObject &deviceConfigJson) {
	const QJsonObject &json = deviceConfigJson;
	deviceConfig.topic = json["topic"].toString();
	if (deviceConfig.topic.isEmpty()) {
		valid = false;
	}
	deviceConfig.deviceType = json["deviceType"].toString();

	if (deviceConfig.deviceType == "publisher") {
		deviceConfig.devicePublisher.interval_ms = json["interval_ms"].toInt();
		deviceConfig.devicePublisher.dataType = json["dataType"].toString();

		if (deviceConfig.devicePublisher.dataType == "string") {
			QJsonArray dataArray = json["data"].toArray();
			for (const auto &value : dataArray) {
				deviceConfig.devicePublisher.data.append(value.toString());
			}
		} else if (deviceConfig.devicePublisher.dataType == "binary") {
			deviceConfig.devicePublisher.filePath = json["filePath"].toString();
		} else {
			valid = false;
		}

	} else if (deviceConfig.deviceType == "receiver") {
		deviceConfig.deviceReciever.targetTopic = json["targetTopic"].toString();
		deviceConfig.deviceReciever.delay_ms = json["delay_ms"].toInt();
	} else {
		valid = false;
	}
}

bool SimulatorDevice::isValid() const {
	return valid;
}

QJsonObject SimulatorDevice::deviceConfigToJson(const DeviceConfig &deviceConfig) {
	QJsonObject deviceJson;
	deviceJson.insert("topic", deviceConfig.topic);
	deviceJson.insert("deviceType", deviceConfig.deviceType);

	if (deviceConfig.deviceType == "publisher") {
		deviceJson.insert("interval_ms", deviceConfig.devicePublisher.interval_ms);
		deviceJson.insert("dataType", deviceConfig.devicePublisher.dataType);

		if (deviceConfig.devicePublisher.dataType == "string") {
			deviceJson.insert("randomData", deviceConfig.devicePublisher.randomData);

			QJsonArray dataArray;
			for (const auto &str : deviceConfig.devicePublisher.data) {
				dataArray.append(str);
			}
			deviceJson.insert("data", dataArray);

		} else /* "binary" */ {
			deviceJson.insert("filePath", deviceConfig.devicePublisher.filePath);
		}

	} else /* "receiver" */ {
		deviceJson.insert("targetTopic", deviceConfig.deviceReciever.targetTopic);
		deviceJson.insert("delay_ms", deviceConfig.deviceReciever.delay_ms);
	}

	return deviceJson;
}

void SimulatorDevice::init() {
	if (deviceConfig.deviceType == "receiver") {
		client.Subscribe({deviceConfig.topic});
	}
}

void SimulatorDevice::startReceiver() {
	recvConnection = connect(&client, &Core::Client::MessageArrived, this, &SimulatorDevice::receiveMessage);
}

void SimulatorDevice::stopReceiver() {
	disconnect(recvConnection);
}

void SimulatorDevice::startPublisher() {
}

void SimulatorDevice::stopPublisher() {
}

void SimulatorDevice::receiveMessage(mqtt::const_message_ptr message) {
	qDebug() << "Simulator device message recieved";
}
