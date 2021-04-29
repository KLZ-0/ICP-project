/**
 * @author Adrián Kálazi (xkalaz00)
 */

// TODO: add .clang-format

#include <QApplication>

#include "test_button.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	TestButton button("Hello world!", nullptr);
	button.resize(200, 100);
	button.show();
	return QApplication::exec();
}
