/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_PUBLISH_WINDOW_HPP
#define MQTT_EXPLORER_PUBLISH_WINDOW_HPP

#include <QWidget>
#include <topic.hpp>

#include "client.hpp"
#include "ui_publish_window.h"

class PublishWindow : public QWidget
{
	Q_OBJECT

public:
	explicit PublishWindow(Topic *initialTopic, Core::Client *mqttClient);

private:
	Ui::PublishWindow ui;
	Topic *topic;
	Core::Client *client;

private slots:
	void sendMessage();
};


#endif //MQTT_EXPLORER_PUBLISH_WINDOW_HPP
