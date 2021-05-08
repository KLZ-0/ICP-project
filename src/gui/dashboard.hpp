/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_DASHBOARD_HPP
#define MQTT_EXPLORER_DASHBOARD_HPP


#include <QWidget>
#include <topic.hpp>

#include "ui_dashboard.h"

class Dashboard : public QWidget
{
	Q_OBJECT

public:
	Dashboard();

private:
	Ui::Dashboard ui;
	QString lastSaveFile = "";

public slots:
	void addTopic(Topic *topic);
	void save();
	void saveAs();
	void saveState(const QString &directory);
};


#endif //MQTT_EXPLORER_DASHBOARD_HPP
