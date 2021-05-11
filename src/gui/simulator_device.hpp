/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once

#include <qobject.h>
#include <qtimer.h>

#include "client.hpp"

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
		DevicePublisher publisher;
		// actual config for receiver
		DeviceReceiver receiver;
	};

public:
	SimulatorDevice(Core::Client &client, const QJsonObject &deviceConfigJson);
	SimulatorDevice(Core::Client &client, DeviceConfig config);
	/**
	 * @brief start simulating device
	*/
	void start();
	/**
	 * @brief stop simulating device
	*/
	void stop();
	/**
	 * @brief convert device config to json object
	 * @param deviceConfig 
	 * @return jsonObject
	*/
	static QJsonObject deviceConfigToJson(const DeviceConfig &config);
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
	void setDeviceConfigfromJson(const QJsonObject &deviceConfigJson);
	/**
	 * @brief initialize client if needed
	*/
	void init();
private:
	int fwidx = 0;
	QTimer timer;
	DeviceConfig config = {};
	bool valid = true;
	Core::Client &client;
	QMetaObject::Connection recvConnection;

private slots:
	/**
	* @brief handle incoming messages for receiver device
	*/
	void receiveMessage(mqtt::const_message_ptr message);
	/**
	 * @brief hadnle publishing of string data
	*/
	void stringPublisher();
	/**
	 * @brief handle publishing of binary data
	*/
	void binaryPublisher();
};
