/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>

Dashboard::Dashboard() {
	ui.setupUi(this);
}

void Dashboard::setClient(Core::Client *mqttClient) {
	client = mqttClient;
}

void Dashboard::addTopic(Topic *topic, QJsonObject *object) {
	qDebug() << "Adding topic" << topic->findFullyQualifiedTopic() << "to dashboard";

	auto item = new DashboardItem(this, topic, client);
	ui.mdiArea->addSubWindow(item);

	if (object != nullptr) {
		item->setupFromJSON(object);
	}
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

void Dashboard::saveState(const QString &filePath) {
	qInfo() << "Saving dashboard to" << filePath;
	QFile file = QFile(filePath);
	file.open(QIODevice::WriteOnly);

	if (file.isOpen()) {
		QJsonObject object;
		createStateJSON(object);
		file.write(QJsonDocument(object).toJson());

		file.close();
	}
}

void Dashboard::createStateJSON(QJsonObject &rootObject) {
	QJsonArray array;

	for (QMdiSubWindow *subWindow : ui.mdiArea->subWindowList()) {
		auto item = dynamic_cast<DashboardItem *>(subWindow);
		item->addToJSONArray(array);
	}

	rootObject["data"] = array;
}
