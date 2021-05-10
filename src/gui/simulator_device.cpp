/**
 * @author Kevin Lackó (xlacko08)
 */

#include "simulator_device.hpp"

#include <qjsonarray.h>
#include <qjsonobject.h>

SimulatorDevice::SimulatorDevice(const QJsonObject &deviceConfigJson) {
	setDeviceConfigfromJson(deviceConfigJson);
}

SimulatorDevice::SimulatorDevice(DeviceConfig deviceConfig) : deviceConfig(deviceConfig) {
}

void SimulatorDevice::start() {

}

void SimulatorDevice::stop() {
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
