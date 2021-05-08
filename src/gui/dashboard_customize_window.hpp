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

private:
	Ui::DashboardCustomizeWindow ui;

signals:
	void titleConfirmed(QString newTitle);

private slots:
	void confirmNewTile();
};


#endif //MQTT_EXPLORER_DASHBOARD_CUSTOMIZE_WINDOW_HPP
