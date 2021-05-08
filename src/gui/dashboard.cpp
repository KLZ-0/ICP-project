/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard.hpp"

#include <QDebug>

#include "dashboard_item.hpp"

Dashboard::Dashboard() {
	ui.setupUi(this);

	ui.mdiArea->addSubWindow(new DashboardItem(this));
	ui.mdiArea->addSubWindow(new DashboardItem(this, "very nice!!!"));
	ui.mdiArea->addSubWindow(new DashboardItem(this, "another subwindow"));
}

void Dashboard::addTopic(Topic *topic) {
	qDebug() << "Adding topic" << topic->getFullyQualifiedTopic() << "to dashboard";
}
