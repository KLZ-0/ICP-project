/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "main_window.hpp"

#include <QDebug>
#include <QPushButton>
#include <QUuid>

#include "publish_window.hpp"
#include "topic_selection_window.hpp"

MainWindow::MainWindow() {
	ui.setupUi(this);

	dataModel = new DataModel(3);
	ui.explorer_tab->setDataModel(dataModel);
	ui.explorer_tab->connectToDashboard(ui.dahboard_tab);

	connect(ui.actionTopics, &QAction::triggered, this, &MainWindow::openTopicsWindow);
	connect(ui.actionSave, &QAction::triggered, ui.explorer_tab, &Explorer::saveStructure);
	connect(ui.actionSave_As, &QAction::triggered, ui.explorer_tab, &Explorer::saveStructureAs);
	connect(ui.actionPublish, &QAction::triggered, this, &MainWindow::openPublishWindow);
	connect(ui.actionQuit, &QAction::triggered, this, &MainWindow::close);

	connect(ui.actionSaveDashboard, &QAction::triggered, ui.dahboard_tab, &Dashboard::save);
	connect(ui.actionSaveDashboard_As, &QAction::triggered, ui.dahboard_tab, &Dashboard::saveAs);
	connect(ui.actionLoadDashboard, &QAction::triggered, ui.explorer_tab, &Explorer::loadDashboard);

	client = new Core::Client(QUuid::createUuid().toString().toStdString());

	qRegisterMetaType<mqtt::const_message_ptr>("mqtt::const_message_ptr");
	connect(client, &Core::Client::Connected, this, &MainWindow::statusConnected);
	connect(client, &Core::Client::ConnectionLost, this, &MainWindow::statusDisconnected);
	connect(client, &Core::Client::MessageArrived, ui.explorer_tab, &Explorer::receiveMessage);

	client->Connect();
	ui.explorer_tab->setClient(client);
	ui.dahboard_tab->setClient(client);
}

void MainWindow::openTopicsWindow() {
	if (topics_window_open) {
		return;
	}

	auto topicsWindow = new TopicSelectionWindow(topics);
	connect(topicsWindow, &TopicSelectionWindow::topicsSelected, this, &MainWindow::handleTopicChange);
	connect(topicsWindow, SIGNAL(destroyed()), this, SLOT(cancelTopicChange()));
	topicsWindow->show();

	topics_window_open = true;
}

void MainWindow::handleTopicChange(const QSet<QString> &new_topics) {

	QSet<QString> subscribe = new_topics - topics;
	QSet<QString> unsubscribe = topics - new_topics;

	client->Unsubscribe(unsubscribe);
	qDebug() << "--- unsubscribe ---";
	for (const QString &topic : unsubscribe) {
		qDebug() << topic;
	}

	client->Subscribe(subscribe);
	qDebug() << "--- subscribe ---";
	for (const QString &topic : subscribe) {
		qDebug() << topic;
	}

	topics = new_topics;
	topics_window_open = false;
}

void MainWindow::cancelTopicChange() {
	topics_window_open = false;
}

MainWindow::~MainWindow() {
	client->Disconnect();
	delete client;
	delete dataModel;
}

void MainWindow::statusConnected() {
	ui.statusbar->showMessage("Connected", 0);
}

void MainWindow::statusDisconnected(const QString &reason) {
	ui.statusbar->showMessage("Disconnected, reason: " + reason, 0);
}

void MainWindow::openPublishWindow() {
	auto publishWindow = new PublishWindow(nullptr, client);
	publishWindow->show();
}
