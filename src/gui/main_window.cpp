/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "main_window.hpp"

#include <QPushButton>

MainWindow::MainWindow() : mainWidget(new QWidget) {
	setCentralWidget(mainWidget);
}
