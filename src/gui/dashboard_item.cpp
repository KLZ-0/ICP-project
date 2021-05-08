/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_item.hpp"

#include <QDebug>
#include <QJsonObject>
#include <QMenu>

#include "dashboard_customize_window.hpp"
#include "publish_window.hpp"

/**
 * @brief Creates a new subwindow
 * @param parent parent widget (though this will be overridden once added to the MDI area)
 * @param widgetTopic topic of this subwindow
 * @param mqttClient connected mqtt client
 */
DashboardItem::DashboardItem(QWidget *parent, Topic *widgetTopic, Core::Client *mqttClient)
	: QMdiSubWindow(parent) {
	topic = widgetTopic;
	client = mqttClient;

	auto contentWidget = new QWidget(this);
	ui.setupUi(contentWidget);
	setWidget(contentWidget);

	setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle(widgetTopic->getName());
	changeDeviceType("");
	updateContent();

	connect(topic, &Topic::changed, this, &DashboardItem::updateContent);

	auto changeTitleAction = new QAction("Customize");
	connect(changeTitleAction, SIGNAL(triggered(bool)), this, SLOT(openDashboardCustomizeWindow()));

	connect(ui.sendButton, &QPushButton::clicked, this, &DashboardItem::publishMessage);

	QMenu *menu = systemMenu();
	menu->addAction(changeTitleAction);
}

/**
 * @brief Opens the customizing window
 */
void DashboardItem::openDashboardCustomizeWindow() {
	auto titleWindow = new DashboardCustomizeWindow(this);
	titleWindow->setDeviceType(ui.devicetype->text());
	titleWindow->setStatusDisplayLength(statusDisplayLenght);
	connect(titleWindow, &DashboardCustomizeWindow::titleChanged, this, &DashboardItem::setWindowTitle);
	connect(titleWindow, &DashboardCustomizeWindow::deviceTypeChanged, this, &DashboardItem::changeDeviceType);
	connect(titleWindow, &DashboardCustomizeWindow::statusDisplayLengthChanged, this, &DashboardItem::changeStatusDisplayLength);
	titleWindow->show();
}

/**
 * @brief Updates the dashboard item contents after customization and on newly arrived messages
 */
void DashboardItem::updateContent() {
	qDebug() << "Update dashboard item";

	QString status = topic->getPayload(0);
	status.truncate(statusDisplayLenght);
	ui.status->setText(status);

	ui.lastseen->setText(topic->getTimestampString());
}

/**
 * @brief Changes device type and shows/hides their block
 * @param newDeviceType string with new device type
 */
void DashboardItem::changeDeviceType(const QString &newDeviceType) {
	ui.devicetype->setText(newDeviceType);
	ui.devicetype->setVisible(newDeviceType != "");
	ui.devicetypeLabel->setVisible(newDeviceType != "");
}

/**
 * @brief Changes status display length and updates the content accordingly
 * @param newLength int with the new length
 */
void DashboardItem::changeStatusDisplayLength(int newLength) {
	statusDisplayLenght = newLength;
	updateContent();
}

/**
 * @brief Adds the properties of this subwindow to the specified JSON array
 * @param jsonArray JSON array
 */
void DashboardItem::addToJSONArray(QJsonArray &jsonArray) {
	QJsonObject object;
	object["title"] = windowTitle();
	object["topic"] = topic->findFullyQualifiedTopic();
	object["status_length"] = statusDisplayLenght;
	object["last_payload"] = topic->getPayload(0);
	object["last_timestamp"] = QString::number(topic->getTimestamp());
	object["device_type"] = ui.devicetype->text();
	jsonArray.append(object);
}

/**
 * @brief Initalizes values from the given JSON object
 * @param object JSON object
 */
void DashboardItem::setupFromJSON(QJsonObject *object) {
	QJsonObject obj = *object;
	QString title = obj["title"].toString();
	QString status_length = obj["status_length"].toString();
	QString last_timestamp = obj["last_timestamp"].toString();
	QString device_type = obj["device_type"].toString();

	setWindowTitle(title);

	bool ok;
	int tmp = status_length.toInt(&ok, 10);
	if (ok) {
		statusDisplayLenght = tmp;
	}

	std::time_t tmp_long = last_timestamp.toLong(&ok, 10);
	if (ok) {
		topic->setTimestamp(tmp_long);
	}

	changeDeviceType(device_type);

	updateContent();
}

/**
 * @brief Publishes the message with the payload from the plain text edit
 */
void DashboardItem::publishMessage() {
	QString send_topic = topic->findFullyQualifiedTopic();
	QString send_payload = ui.plainTextEdit->toPlainText();

	mqtt::message_ptr_builder builder;

	builder.topic(send_topic.toStdString());
	builder.payload(send_payload.toStdString());

	client->Publish(builder.finalize());

	qDebug() << "sent" << send_topic << send_payload;
}
