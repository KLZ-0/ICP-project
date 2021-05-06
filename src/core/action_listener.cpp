/**
 * @author Kevin Lackó (xlacko08)
 */


#include "action_listener.hpp"

#include <mqtt/token.h>

namespace Core
{
	void ActionListener::on_success(const mqtt::token &tok) {
		std::cout << " success";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		auto top = tok.get_topics();
		if (top && !top->empty())
			std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
		std::cout << std::endl;
	}
	void ActionListener::on_failure(const mqtt::token &tok) {
		std::cout << "Failure";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		std::cout << std::endl;
	}
} // namespace Core
