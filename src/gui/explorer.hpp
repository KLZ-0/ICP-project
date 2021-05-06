/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_EXPLORER_HPP
#define MQTT_EXPLORER_EXPLORER_HPP


#include <mqtt/message.h>
#include <QWidget>

#include "ui_explorer.h"

class Explorer : public QWidget
{
	Q_OBJECT

public:
	Explorer();

private:
	Ui::Explorer ui;
	int dummyCount = 0;

private slots:
	void updateContentBlock(QTreeWidgetItem *tree_item, int column);
	void receiveMessage(mqtt::message &message);
	void dummyCallback();
};


#endif //MQTT_EXPLORER_EXPLORER_HPP
