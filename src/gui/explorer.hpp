/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_EXPLORER_HPP
#define MQTT_EXPLORER_EXPLORER_HPP


#include <QPlainTextEdit>
#include <QWidget>
#include <client.hpp>
#include <mqtt/message.h>

#include "dashboard.hpp"
#include "dashboard_item.hpp"
#include "data_model.hpp"
#include "explorer_item.hpp"
#include "ui_explorer.h"

/**
 * @class Explorer
 * @brief Represents the explorer tab
 * The UI contains a treeview for topics and a content QTabWidget for displaying the topic history
 */
class Explorer : public QWidget
{
	Q_OBJECT

public:
	Explorer();
	void setDataModel(DataModel *model);
	void setClient(Core::Client *mqttClient);
	void connectToDashboard(Dashboard *dashboard);

private:
	Ui::Explorer ui;
	DataModel *dataModel;
	Core::Client *client;
	QString lastSaveDir = "";

	int messageLimit = 3;
	QVector<QPlainTextEdit *> contentEdits;

	ExplorerItem *findOrCreateItemFromTopic(QString &topic);
	ExplorerItem *findOrCreateRootChild(QString &name);

	// TODO: move this to settings
	const int MAX_MESSAGE_RENDER_LENGTH = 500;

signals:
	void dashboardRequest(Topic *topic, QJsonObject *object = nullptr);

public slots:
	void setMessageLimit();
	void updateContentBlock();
	void receiveMessage(mqtt::const_message_ptr message);
	void saveState(const QString &directory);
	void saveStructure();
	void saveStructureAs();
	void openPublishWindow(QTreeWidgetItem *item, int column);
	void loadDashboard();

private slots:
	void sendDashboardRequest();
};


#endif //MQTT_EXPLORER_EXPLORER_HPP
