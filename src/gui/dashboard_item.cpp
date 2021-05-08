/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_item.hpp"

#include <QDebug>
#include <QJsonObject>
#include <QMenu>

#include "dashboard_customize_window.hpp"

DashboardItem::DashboardItem(QWidget *parent, Topic *widgetTopic)
	: QMdiSubWindow(parent) {
	topic = widgetTopic;

	auto contentWidget = new QWidget(this);
	ui.setupUi(contentWidget);
	setWidget(contentWidget);

	setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle(widgetTopic->getName());
	changeDeviceType("");
	updateContent();

	connect(topic, &Topic::changed, this, &DashboardItem::processTopicChange);

	auto changeTitleAction = new QAction("Customize");
	connect(changeTitleAction, SIGNAL(triggered(bool)), this, SLOT(openDashboardCustomizeWindow()));

	QMenu *menu = systemMenu();
	menu->addAction(changeTitleAction);
}

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
 * Saves the current timestamp and updates the dashboard item content
 */
void DashboardItem::processTopicChange() {
	updateContent();
}

void DashboardItem::updateContent() {
	qDebug() << "Update dashboard item";

	QString status = topic->getPayload(0);
	status.truncate(statusDisplayLenght);
	ui.status->setText(status);

	ui.lastseen->setText(topic->getTimestampString());
}

void DashboardItem::changeDeviceType(const QString &newDeviceType) {
	ui.devicetype->setText(newDeviceType);
	ui.devicetype->setVisible(newDeviceType != "");
	ui.devicetypeLabel->setVisible(newDeviceType != "");
}

void DashboardItem::changeStatusDisplayLength(int newLength) {
	statusDisplayLenght = newLength;
	updateContent();
}

void DashboardItem::addToJSONArray(QJsonArray &jsonArray) {
	QJsonObject object;
	object["title"] = windowTitle();
	object["topic"] = topic->findFullyQualifiedTopic();
	object["status_length"] = statusDisplayLenght;
	object["last_payload"] = topic->getPayload(0);
	object["last_timestamp"] = QString::number(topic->getTimestamp());
	jsonArray.append(object);
}

void DashboardItem::setupFromJSON(QJsonObject *object) {
	QJsonObject obj = *object;
	QString title = obj["title"].toString();
	QString status_length = obj["status_length"].toString();
	QString last_timestamp = obj["last_timestamp"].toString();

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

	updateContent();
}
