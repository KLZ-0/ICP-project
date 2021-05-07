/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include <QApplication>

#include "core/client.hpp"
#include "test_button.hpp"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	Core::Client client("explorer");
	client.Connect();
	TestButton button("Disconnect", nullptr, &client);
	button.resize(200, 100);
	button.show();
	TestButton button1("subscribe", nullptr, &client);
	button1.resize(200, 100);
	button1.show();
	QObject::connect(&button, SIGNAL(clicked()), &client, SLOT(Disconnect()));
	QObject::connect(&button1, SIGNAL(clicked()), &button1, SLOT(pahotest()));

	
	return QApplication::exec();
}
