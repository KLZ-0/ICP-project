/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_DASHBOARD_HPP
#define MQTT_EXPLORER_DASHBOARD_HPP


#include <QJsonDocument>
#include <QWidget>
#include <client.hpp>
#include <topic.hpp>

#include "dashboard_item.hpp"
#include "ui_dashboard.h"

/**
 * @class Dashboard
 * @brief Represents the dashboard tab
 * The UI contains an MDI area for subwindows
 */
class Dashboard : public QWidget
{
	Q_OBJECT

public:
	Dashboard();
	void setClient(Core::Client *mqttClient);

private:
	Ui::Dashboard ui;
	Core::Client *client;
	QString lastSaveFile = "";
	void createStateJSON(QJsonObject &rootObject);

public slots:
	void addTopic(Topic *topic, QJsonObject *object = nullptr);
	void save();
	void saveAs();
	void saveState(const QString &filePath);
};


#endif //MQTT_EXPLORER_DASHBOARD_HPP
