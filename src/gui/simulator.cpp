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

void Simulator::load() {
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "",
													tr("Simulator config files (*.json)"));

	qInfo() << "Loading simulator config from" << filePath;
	QFile file = QFile(filePath);
	file.open(QIODevice::ReadOnly);

	if (!file.isOpen()) {
		qWarning() << "Can't open simulator config file for reading";
		return;
	}

	lastSaveFile = filePath;
	ui.configEdit->setPlainText(file.readAll());

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	QJsonArray dataArray = doc["data"].toArray();

	for (auto item : dataArray) {
		QJsonObject itemObject = item.toObject();
	}

	file.close();
}

void Simulator::save() {
	if (lastSaveFile == "") {
		saveAs();
	} else {
		saveState(lastSaveFile);
	}
}

void Simulator::saveAs() {
	QString userFile = QFileDialog::getSaveFileName(this, tr("Save File"), "",
													tr("Simulator config files (*.json)"));

	if (userFile == "") {
		return;
	}

	saveState(userFile);

	lastSaveFile = userFile;
}

void Simulator::saveState(const QString &filePath) {
	qInfo() << "Saving simulator config to" << filePath;
	QFile file = QFile(filePath);
	file.open(QIODevice::WriteOnly);

	if (file.isOpen()) {
		file.write(ui.configEdit->toPlainText().toUtf8());
		file.close();
	}
}
