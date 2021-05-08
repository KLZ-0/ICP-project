/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard.hpp"

#include <QDebug>
#include <QFileDialog>

#include "dashboard_item.hpp"

Dashboard::Dashboard() {
	ui.setupUi(this);
}

void Dashboard::addTopic(Topic *topic) {
	qDebug() << "Adding topic" << topic->findFullyQualifiedTopic() << "to dashboard";

	ui.mdiArea->addSubWindow(new DashboardItem(this, topic));
}

void Dashboard::save() {
	if (lastSaveFile == "") {
		saveAs();
	} else {
		saveState(lastSaveFile);
	}
}

void Dashboard::saveAs() {
	QString userFile = QFileDialog::getSaveFileName(this, tr("Save File"),
													"",
													tr("Dashboard configuration files (*.json)"));

	if (userFile == "") {
		return;
	}

	saveState(userFile);

	lastSaveFile = userFile;
}

void Dashboard::saveState(const QString &directory) {
	qInfo() << "Saving dashboard to" << directory;
}
