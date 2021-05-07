/**
* @author Adrián Kálazi (xkalaz00)
*/

#include <mqtt/client.h>

int main(int argc, char *argv[]) {
	std::cout << "sending" << std::endl;

	const std::string SERVER_ADDRESS = "tcp://test.mosquitto.org:1883";
	const std::string CLIENT_ID = "someoneunknown";
	const std::string TOPIC = "sr1";

	const std::string PAYLOAD1 = "test";
	const char *PAYLOAD2 = "test 2";

	// Create a client

	mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);

	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);

	try {
		// Connect to the client

		cli.connect(connOpts);

		// Publish using a message pointer.

		auto msg = mqtt::make_message(TOPIC, PAYLOAD1);
		msg->set_qos(0);

		cli.publish(msg);

		// Now try with itemized publish.

		cli.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2), 0, false);

		// Disconnect

		cli.disconnect();
	} catch (const mqtt::exception &exc) {
		std::cerr << "Error: " << exc.what() << " ["
				  << exc.get_reason_code() << "]" << std::endl;
	}
}
