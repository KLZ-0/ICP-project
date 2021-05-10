/**
 * @author Kevin Lackó (xlacko08)
 */

#include "simulator.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>

/**
 * @brief Initialize the simulator tab
 */
Simulator::Simulator() {
	ui.setupUi(this);
}

/**
 * @brief Save action
 * Save the simulator config to a previously used savefile or ask the user for a new file
 */
void Simulator::save() {
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
void Simulator::saveAs() {
	QString userFile = QFileDialog::getSaveFileName(this, tr("Save File"),
													"",
													tr("Simulator configuration files (*.json)"));

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
void Simulator::saveState(const QString &filePath) {
	qInfo() << "Saving simulator config to" << filePath;
	QFile file = QFile(filePath);
	file.open(QIODevice::WriteOnly);

	if (file.isOpen()) {
		QJsonObject object;
		// create json on object
		file.write(QJsonDocument(object).toJson());

		file.close();
	}
}
