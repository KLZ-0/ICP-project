/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_item.hpp"

#include <QDebug>
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
	ui.topic->hide();
	ui.topicLabel->hide();
	updateContent();

	connect(topic, &Topic::changed, this, &DashboardItem::updateContent);

	auto changeTitleAction = new QAction("Customize");
	connect(changeTitleAction, SIGNAL(triggered(bool)), this, SLOT(openDashboardCustomizeWindow()));

	QMenu *menu = systemMenu();
	menu->addAction(changeTitleAction);
}

void DashboardItem::openDashboardCustomizeWindow() {
	auto titleWindow = new DashboardCustomizeWindow(this);
	titleWindow->setDeviceType(ui.devicetype->text());
	connect(titleWindow, &DashboardCustomizeWindow::titleChanged, this, &DashboardItem::setWindowTitle);
	connect(titleWindow, &DashboardCustomizeWindow::deviceTypeChanged, this, &DashboardItem::changeDeviceType);
	titleWindow->show();
}

void DashboardItem::updateContent() {
	qDebug() << "Update dashboard item";
	ui.topic->setText(topic->findFullyQualifiedTopic());
	ui.status->setText(topic->getPayload(0));

	if (lastTimestamp != 0) {
		ui.lastseen->setText("time");
	} else {
		ui.lastseen->setText("");
	}
}

void DashboardItem::changeDeviceType(const QString &newDeviceType) {
	ui.devicetype->setText(newDeviceType);
	ui.devicetype->setVisible(newDeviceType != "");
	ui.devicetypeLabel->setVisible(newDeviceType != "");
}
