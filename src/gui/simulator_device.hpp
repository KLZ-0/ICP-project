/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <qobject.h>
#include <qtimer.h>

class SimulatorDevice : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief Device which sends data
	*/
	struct DevicePublisher
	{
		// periodicity for sending the data
		int interval_ms;
		// "string" or "binary"
		QString dataType;
		// choose data randomly vs consecutively
		bool randomData;
		// string data to be sent
		QVector<QString> data;
		// binary file to be sent
		QString filePath;
	};

	struct DeviceReceiver
	{
		// the topic to which we want to publish the update
		QString targetTopic;
		// delay after which to publish the update
		int delay_ms;
	};

	/**
	 * @brief configuration data of a simulated device
	*/
	struct DeviceConfig
	{
		// publish or recieve data from this topic
		QString topic;
		// select device type ("receiver"/"publisher")
		QString deviceType;
		// actual config for publisher
		DevicePublisher devicePublisher;
		// actual config for receiver
		DeviceReceiver deviceReciever;
	};

public:
	SimulatorDevice(const QJsonObject& deviceConfigJson);
	SimulatorDevice(DeviceConfig deviceConfig);

	void start();

	void stop();

	/**
	 * @brief serialize device config to json
	 * @return device config as QJsonObject
	*/
	QJsonObject toJson() const;
	/**
	 * @brief check if the device was constructed correctly
	*/
	bool isValid() const;

private:
	/**
	 * @brief parse json object
	 * @param  
	*/
	void setDeviceConfigfromJson(const QJsonObject& deviceConfigJson);

private:
	QTimer timer;
	DeviceConfig deviceConfig = {};
	bool valid = true;
};
