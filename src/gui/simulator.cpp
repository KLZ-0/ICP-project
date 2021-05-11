/**
 * @file
 * @author Kevin Lackó (xlacko08)
 */

#include "simulator.hpp"

#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <memory>

Simulator::Simulator() : client("simulator") {
	ui.setupUi(this);

	client.Connect();

	connect(ui.configButton, SIGNAL(clicked(bool)), this, SLOT(configureSimulator()));
	connect(ui.startButton, SIGNAL(clicked(bool)), this, SLOT(startSimulator()));
	connect(ui.stopButton, SIGNAL(clicked(bool)), this, SLOT(stopSimulator()));
	connect(ui.configEdit, SIGNAL(textChanged()), this, SLOT(configChanged()));
	connect(ui.showConfigButton, SIGNAL(clicked(bool)), this, SLOT(showCurrentConfig()));
}

void Simulator::load() {
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "",
													tr("Simulator config files (*.json)"));

	qInfo() << "Loading simulator config from" << filePath;
	QFile file = QFile(filePath);
	QFileInfo fileInfo(file.fileName());
	fileName = fileInfo.fileName();
	justLoaded = true;
	ui.openFileName->setText(fileName);

	file.open(QIODevice::ReadOnly);
	if (!file.isOpen()) {
		qWarning() << "Can't open simulator config file for reading";
		return;
	}

	lastSaveFile = filePath;
	ui.configEdit->setPlainText(file.readAll());

	emit statusBarUpdate("Config file loaded");
	file.close();
}

Simulator::~Simulator() {
	client.Disconnect();
	clearDevices();
}

void Simulator::clearDevices() {
	for (auto* device : devices) {
		delete device;
	}
	devices.clear();
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
	QFileInfo fileInfo(file.fileName());
	fileName = fileInfo.fileName();
	ui.openFileName->setText(fileName);

	file.open(QIODevice::WriteOnly);
	if (file.isOpen()) {
		file.write(ui.configEdit->toPlainText().toUtf8());
		file.close();
	}

	emit statusBarUpdate("Config file saved");
}

void Simulator::showCurrentConfig() {
	if (!configured) {
		emit statusBarUpdate("Simulator not configured");
		return;
	}
	fileName = "";
	lastSaveFile = "";


	SimulatorDevice::DeviceConfig config;
	config.topic = "sr1";
	config.deviceType = "publisher";
	config.publisher.randomData = true;
	config.publisher.dataType = "string";
	config.publisher.interval_ms = 500;
	config.publisher.data = {"abc", "123", "last one"};
	SimulatorDevice device(client, config);
	QJsonObject jsonObject;
	jsonObject = device.toJson();
	QJsonArray jsonArray;
	jsonArray.append(jsonObject);
	ui.configEdit->setPlainText(QJsonDocument(jsonArray).toJson());
}

void Simulator::configureSimulator() {
	if (running) {
		emit statusBarUpdate("Can't configure - simulator running");
		return;
	}

	clearDevices();

	QJsonArray dataArray = QJsonDocument::fromJson(ui.configEdit->toPlainText().toUtf8()).array();
	if (dataArray.isEmpty()) {
		emit statusBarUpdate("No devices defined in the config file");
		return;
	}
	for (const auto &data : dataArray) {
		QJsonObject deviceConfigJson = data.toObject();
		devices.append(new SimulatorDevice(client, deviceConfigJson));
		if (!devices.back()->isValid()) {
			devices.removeLast();
		}
	}
	if (devices.isEmpty()) {
		emit statusBarUpdate("No valid devices defined in the config file");
		return;
	}

	configured = true;
	ui.configStatus->setText("Configured");
	ui.fileStatus->setText("In use");
	emit statusBarUpdate("Simulator configured");
}

void Simulator::startSimulator() {
	if (running) {
		return;
	}
	if (!configured) {
		emit statusBarUpdate("Can't start - simulator not configured");
		return;
	}

	for (auto *device : devices) {
		device->start();
	}

	running = true;
	ui.simStatus->setText("Running");
	emit statusBarUpdate("Simulator started");
	qDebug() << "Simulator: starting " << devices.size() << "devices";
}

void Simulator::stopSimulator() {
	if (!running) {
		return;
	}

	for (auto *device : devices) {
		device->stop();
	}

	running = false;
	ui.simStatus->setText("Stopped");
	emit statusBarUpdate("Simulator stopped");
	qDebug() << "Simulator: stopping " << devices.size() << "devices";
}

void Simulator::configChanged() {
	ui.fileStatus->setText("Not in use");
	if (!justLoaded) {
		QString unsavedFileName = fileName + "*";
		ui.openFileName->setText(unsavedFileName);
	} else {
		justLoaded = false;
	}
}
