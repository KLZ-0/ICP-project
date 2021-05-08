/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_DASHBOARD_ITEM_HPP
#define MQTT_EXPLORER_DASHBOARD_ITEM_HPP


#include <QJsonArray>
#include <QJsonValue>
#include <QMdiSubWindow>
#include <QWidget>
#include <client.hpp>
#include <topic.hpp>

#include "ui_dashboard_item.h"

/**
 * @class DashboardItem
 * @brief Represents a dashboard subwindow
 * This window has it's own lifecycle
 */
class DashboardItem : public QMdiSubWindow
{
	Q_OBJECT

public:
	explicit DashboardItem(QWidget *parent, Topic *widgetTopic, Core::Client *mqttClient);
	void addToJSONArray(QJsonArray &jsonArray);
	void setupFromJSON(QJsonObject *object);

private:
	Ui::DashboardItem ui;
	Core::Client *client;
	Topic *topic;
	int statusDisplayLenght = 18;

private slots:
	void openDashboardCustomizeWindow();
	void processTopicChange();
	void updateContent();
	void changeDeviceType(const QString &newDeviceType);
	void changeStatusDisplayLength(int newLength);
	void publishMessage();
};


#endif //MQTT_EXPLORER_DASHBOARD_ITEM_HPP
