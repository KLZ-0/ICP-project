/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard.hpp"

#include <QDebug>

#include "dashboard_item.hpp"

Dashboard::Dashboard() {
	ui.setupUi(this);
}

void Dashboard::addTopic(Topic *topic) {
	qDebug() << "Adding topic" << topic->findFullyQualifiedTopic() << "to dashboard";

	ui.mdiArea->addSubWindow(new DashboardItem(this, topic));
}
