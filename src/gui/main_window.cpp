/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "main_window.hpp"

#include <QDebug>
#include <QPushButton>

#include "topic_selection_window.hpp"

MainWindow::MainWindow() {
	ui.setupUi(this);

	dataModel = new DataModel(3);
	ui.explorer_tab->setDataModel(dataModel);

	connect(ui.actionTopics, &QAction::triggered, this, &MainWindow::openTopicsWindow);

	client = new Core::Client("thisclient");

	connect(client, SIGNAL(Connected()), this, SLOT(statusConnected()));
	connect(client, SIGNAL(ConnectionLost(const QString &)), this, SLOT(statusDisconnected(const QString &)));

	client->Connect();
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

	qDebug() << "--- subscribe ---";
	for (const QString &topic : subscribe) {
		qDebug() << topic;
	}

	qDebug() << "--- unsubscribe ---";
	for (const QString &topic : unsubscribe) {
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
	qDebug() << "connected";
}

void MainWindow::statusDisconnected(const QString &reason) {
	qDebug() << "disconnected" << reason;
}
