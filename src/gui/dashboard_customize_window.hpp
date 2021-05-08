/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_DASHBOARD_CUSTOMIZE_WINDOW_HPP
#define MQTT_EXPLORER_DASHBOARD_CUSTOMIZE_WINDOW_HPP

#include <QWidget>

#include "ui_dashboard_customize_window.h"

class DashboardCustomizeWindow : public QWidget
{
	Q_OBJECT
public:
	explicit DashboardCustomizeWindow(QWidget *callerWidget);
	void setDeviceType(QString initalDeviceType);

private:
	Ui::DashboardCustomizeWindow ui;
	QString oldTitle;
	QString oldDeviceType;

signals:
	void titleChanged(QString newTitle);
	void deviceTypeChanged(QString newTitle);

private slots:
	void confirmChanges();
};


#endif //MQTT_EXPLORER_DASHBOARD_CUSTOMIZE_WINDOW_HPP
