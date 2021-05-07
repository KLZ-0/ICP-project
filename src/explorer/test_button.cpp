/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "test_button.hpp"

#include <mqtt/async_client.h>
#include <mqtt/client.h>
#include <qset.h>

TestButton::TestButton(const QString &text, QWidget *parent, Core::Client *client)
	: QPushButton(text, parent), client_(client) {
	//connect(this, SIGNAL(clicked()),
			//this, SLOT(pahotest()));
}

void TestButton::pahotest() {
	//std::cout << "etf" << std::endl;

	const std::string SERVER_ADDRESS = "tcp://test.mosquitto.org:1883";
	const std::string CLIENT_ID = "someoneunknown";
	const std::string TOPIC = "sr1";

	const std::string PAYLOAD1 = "test";
	const char *PAYLOAD2 = "test 2";

	QSet<QString> topics;
	topics.insert(TOPIC.c_str());
	client_->Subscribe(topics);

	// Create a client

	//mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);

	//mqtt::connect_options connOpts;
	//connOpts.set_keep_alive_interval(20);
	//connOpts.set_clean_session(true);

	//try {
	//	// Connect to the client

	//	cli.connect(connOpts);

		// Publish using a message pointer.

		//auto msg = mqtt::make_message(TOPIC, PAYLOAD1);
		//msg->set_qos(0);

		//client_->publish(msg);

		//// Now try with itemized publish.

		//client_.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2), 0, false);

	//	// Disconnect

	//	cli.disconnect();
	//} catch (const mqtt::exception &exc) {
	//	std::cerr << "Error: " << exc.what() << " ["
	//			  << exc.get_reason_code() << "]" << std::endl;
	//}
}
