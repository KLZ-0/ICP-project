/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_PUBLISH_WINDOW_HPP
#define MQTT_EXPLORER_PUBLISH_WINDOW_HPP

#include <QWidget>
#include <topic.hpp>

#include "ui_publish_window.h"

class PublishWindow : public QWidget
{
	Q_OBJECT

public:
	explicit PublishWindow(Topic *initialTopic);

private:
	Ui::PublishWindow ui;
	Topic *topic;

private slots:
	void sendMessage();
};


#endif //MQTT_EXPLORER_PUBLISH_WINDOW_HPP
