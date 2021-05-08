/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_DASHBOARD_ITEM_HPP
#define MQTT_EXPLORER_DASHBOARD_ITEM_HPP


#include <QJsonArray>
#include <QJsonValue>
#include <QMdiSubWindow>
#include <QWidget>
#include <topic.hpp>

#include "ui_dashboard_item.h"

class DashboardItem : public QMdiSubWindow
{
	Q_OBJECT

public:
	explicit DashboardItem(QWidget *parent, Topic *widgetTopic);
	void addToJSONArray(QJsonArray &jsonArray);

private:
	Ui::DashboardItem ui;
	Topic *topic;
	int statusDisplayLenght = 18;

private slots:
	void openDashboardCustomizeWindow();
	void processTopicChange();
	void updateContent();
	void changeDeviceType(const QString &newDeviceType);
	void changeStatusDisplayLength(int newLength);
};


#endif //MQTT_EXPLORER_DASHBOARD_ITEM_HPP
