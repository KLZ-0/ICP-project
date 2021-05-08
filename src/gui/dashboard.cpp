/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>

/**
 * @brief Initialize the dashboard tab
 */
Dashboard::Dashboard() {
	ui.setupUi(this);
}

/**
 * @brief Setter for mqtt client
 * @param mqttClient connected mqtt client
 */
void Dashboard::setClient(Core::Client *mqttClient) {
	client = mqttClient;
}

/**
 * @brief Adds a new topic to the dashboard
 * @param topic topic
 * @param object JSON object (if further initialization is needed when loading from a file)
 */
void Dashboard::addTopic(Topic *topic, QJsonObject *object) {
	qDebug() << "Adding topic" << topic->findFullyQualifiedTopic() << "to dashboard";

	auto item = new DashboardItem(this, topic, client);
	ui.mdiArea->addSubWindow(item);
	item->show();

	if (object != nullptr) {
		item->setupFromJSON(object);
	}
}

/**
 * @brief Save action
 * Save the dashboard to a previously used savefile or ask the user for a new file
 */
void Dashboard::save() {
	if (lastSaveFile == "") {
		saveAs();
	} else {
		saveState(lastSaveFile);
	}
}

/**
 * @brief Save As action
 * Ask the user for a save file and save the dashboard to it
 */
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

/**
 * @brief Does the actual saving
 * Saves the dashboard to a JSON file
 * @param filePath path to a savefile
 */
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

/**
 * @brief Fills the given JSON object with objects representing the subwindows
 * @param rootObject root JSON object
 */
void Dashboard::createStateJSON(QJsonObject &rootObject) {
	QJsonArray array;

	for (QMdiSubWindow *subWindow : ui.mdiArea->subWindowList()) {
		auto item = dynamic_cast<DashboardItem *>(subWindow);
		item->addToJSONArray(array);
	}

	rootObject["data"] = array;
}
