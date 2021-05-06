/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "main_window.hpp"

#include <QDebug>
#include <QPushButton>

#include "topic_selection_window.hpp"

MainWindow::MainWindow() {
	ui.setupUi(this);

	connect(ui.actionTopics, &QAction::triggered, this, &MainWindow::openTopicsWindow);
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

void MainWindow::handleTopicChange(const QVector<QString> &new_topics) {
	topics = new_topics;

	qDebug() << "------";
	for (const QString &topic : topics) {
		qDebug() << topic;
	}

	topics_window_open = false;
}

void MainWindow::cancelTopicChange() {
	topics_window_open = false;
}
