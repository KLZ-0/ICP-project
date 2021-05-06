/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "main_window.hpp"

#include <QPushButton>

#include "topic_selection_window.hpp"

MainWindow::MainWindow() {
	ui.setupUi(this);

	connect(ui.actionTopics, &QAction::triggered, this, &MainWindow::openTopicsWindow);
}

void MainWindow::openTopicsWindow() {
	auto topicsWindow = new TopicSelectionWindow();
	topicsWindow->show();
}
