/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_EXPLORER_HPP
#define MQTT_EXPLORER_EXPLORER_HPP


#include <QWidget>

#include "ui_explorer.h"

class Explorer : public QWidget
{
	Q_OBJECT

public:
	Explorer();

private:
	Ui::Explorer ui;

private slots:
	void setContent(QTreeWidgetItem *item, int column);
};


#endif //MQTT_EXPLORER_EXPLORER_HPP
