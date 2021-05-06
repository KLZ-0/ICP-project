/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_DASHBOARD_ITEM_HPP
#define MQTT_EXPLORER_DASHBOARD_ITEM_HPP


#include <QWidget>

#include "ui_dashboard_item.h"

class DashboardItem : public QWidget
{
	Q_OBJECT

public:
	explicit DashboardItem(QWidget *parent, QString content = "");

private:
	Ui::DashboardItem ui;
};


#endif //MQTT_EXPLORER_DASHBOARD_ITEM_HPP
