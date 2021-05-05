/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_DASHBOARD_HPP
#define MQTT_EXPLORER_DASHBOARD_HPP


#include <QWidget>

#include "ui_dashboard.h"

class Dashboard : public QWidget
{
	Q_OBJECT
public:
	Dashboard();

private:
	Ui::Dashboard ui;
};


#endif //MQTT_EXPLORER_DASHBOARD_HPP
