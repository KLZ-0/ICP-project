/**
 * @author Adrián Kálazi (xkalaz00)
 */

// TODO: add .clang-format

#include <QApplication>

#include "test_button.h"
#include "gui/main_window.hpp"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	MainWindow window;
	window.show();

	return QApplication::exec();
}
