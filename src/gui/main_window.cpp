/**
 * @author Adrián Kálazi (xkalaz00)
 * @author Kevin Lackó (xlacko08)
 */

#include "main_window.hpp"

#include <QDebug>
#include <QPushButton>

#include "publish_window.hpp"
#include "topic_selection_window.hpp"

/**
 * @brief Initializes the main window
 */
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

	connect(ui.actionLoadSimulator, &QAction::triggered, ui.simulator_tab, &Simulator::load);
	connect(ui.actionSaveSimulator, &QAction::triggered, ui.simulator_tab, &Simulator::save);
	connect(ui.actionSaveSimulator_As, &QAction::triggered, ui.simulator_tab, &Simulator::saveAs);
	connect(ui.simulator_tab, &Simulator::statusBarUpdate, this, &MainWindow::statusBarUpdate);

	client = new Core::Client("explorer");

	qRegisterMetaType<mqtt::const_message_ptr>("mqtt::const_message_ptr");
	connect(client, &Core::Client::Connected, this, &MainWindow::statusConnected);
	connect(client, &Core::Client::ConnectionLost, this, &MainWindow::statusDisconnected);
	connect(client, &Core::Client::MessageArrived, ui.explorer_tab, &Explorer::receiveMessage);

	client->Connect();
	ui.explorer_tab->setClient(client);
	ui.dahboard_tab->setClient(client);
}

/**
 * @brief Opens the topic selection window
 * Only one of these windows should be open at any given time
 * The window will delete itself on close
 */
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

/**
 * @brief Processes topic changes
 * Performs a topic difference and subscribes/unsubscribes to/from the calculated topics
 * @param new_topics new topic list to which we should be subscribed after this method call
 */
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

/**
 * @brief Cancels the topic change and marks the topic window as closed
 */
void MainWindow::cancelTopicChange() {
	topics_window_open = false;
}

/**
 * @brief Destructs the main window and deletes the data model
 */
MainWindow::~MainWindow() {
	client->Disconnect();
	delete client;
	delete dataModel;
}

/**
 * @brief Show connected status in statusbar
 */
void MainWindow::statusConnected() {
	ui.statusbar->showMessage("Connected", 0);
}

/**
 * @brief Show disconnected status in statusbar
 */
void MainWindow::statusDisconnected(const QString &reason) {
	ui.statusbar->showMessage("Disconnected, reason: " + reason, 0);
}

/**
 * @brief Open the publish window
 * Multiple of these windows can be open at the same time
 */
void MainWindow::openPublishWindow() {
	auto publishWindow = new PublishWindow(nullptr, client);
	publishWindow->show();
}

/**
 * @brief show any status in statusbar
 * @param status
*/
void MainWindow::statusBarUpdate(const QString &status) {
	ui.statusbar->showMessage(status, 0);
}
