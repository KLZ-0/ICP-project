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
	ui.label->setText(widgetTopic->findFullyQualifiedTopic());
	connect(topic, &Topic::changed, this, &DashboardItem::updateContent);

	auto changeTitleAction = new QAction("Costomize");
	connect(changeTitleAction, SIGNAL(triggered(bool)), this, SLOT(openDashboardCustomizeWindow()));

	QMenu *menu = systemMenu();
	menu->addAction(changeTitleAction);
}

void DashboardItem::openDashboardCustomizeWindow() {
	auto titleWindow = new DashboardCustomizeWindow(this);
	connect(titleWindow, &DashboardCustomizeWindow::titleConfirmed, this, &DashboardItem::setWindowTitle);
	titleWindow->show();
}

void DashboardItem::updateContent() {
	qDebug() << "Update dashboard item";
}
