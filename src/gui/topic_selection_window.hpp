/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_TOPIC_SELECTION_WINDOW_HPP
#define MQTT_EXPLORER_TOPIC_SELECTION_WINDOW_HPP

#include <QWidget>

#include "ui_topic_selection_window.h"

class TopicSelectionWindow : public QWidget
{
	Q_OBJECT

public:
	TopicSelectionWindow();

private:
	Ui::TopicSelectionWindow ui;

private slots:
	void addNewTopic();
};


#endif //MQTT_EXPLORER_TOPIC_SELECTION_WINDOW_HPP
