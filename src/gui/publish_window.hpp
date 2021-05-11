/**
 * @file
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_PUBLISH_WINDOW_HPP
#define MQTT_EXPLORER_PUBLISH_WINDOW_HPP

#include <QWidget>
#include <topic.hpp>

#include "client.hpp"
#include "ui_publish_window.h"

/**
 * @class PublishWindow
 * @brief Represents a window for publishing a message
 * Used in places where a separate window is needed
 * This window has it's own lifecycle
 * @note publishing a message from the dashboard works independently of this window
 */
class PublishWindow : public QWidget
{
	Q_OBJECT

public:
	explicit PublishWindow(Topic *initialTopic, Core::Client *mqttClient);

private:
	Ui::PublishWindow ui;
	Core::Client *client;

private slots:
	void sendMessage();
};


#endif //MQTT_EXPLORER_PUBLISH_WINDOW_HPP
