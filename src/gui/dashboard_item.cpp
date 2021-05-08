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
	lastTimestamp = std::time(nullptr);

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
	lastTimestamp = std::time(nullptr);
	updateContent();
}

void DashboardItem::updateContent() {
	qDebug() << "Update dashboard item";

	QString status = topic->getPayload(0);
	status.truncate(statusDisplayLenght);
	ui.status->setText(status);

	if (lastTimestamp != 0) {
		char mbstr[100];
		if (std::strftime(mbstr, sizeof(mbstr), "%F %T", std::localtime(&lastTimestamp))) {
			ui.lastseen->setText(mbstr);
		}
	} else {
		ui.lastseen->setText("");
	}
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
	jsonArray.append(object);
}
