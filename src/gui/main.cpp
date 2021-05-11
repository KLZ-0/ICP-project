/**
 * @file
 * @author Adrián Kálazi (xkalaz00)
 */

#include <QApplication>

#include "main_window.hpp"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	MainWindow window;
	window.show();

	return QApplication::exec();
}
