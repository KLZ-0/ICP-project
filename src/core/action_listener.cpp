/**
 * @author Kevin Lackó (xlacko08)
 */


#include "action_listener.hpp"

#include <mqtt/token.h>

#include "utils.hpp"

namespace Core
{
	void ActionListener::on_success(const mqtt::token &tok) {
		if (tok.get_message_id() != 0)
			LOG("Success for token: [" << tok.get_message_id() << "]\n");
		auto top = tok.get_topics();
		if (top && !top->empty())
			LOG("\ttoken topic: '" << (*top)[0] << "', ...\n");
		LOG("\n");
	}
	void ActionListener::on_failure(const mqtt::token &tok) {
		if (tok.get_message_id() != 0)
			LOG("Failure for token: [" << tok.get_message_id() << "]\n");
		LOG("\n");
	}
} // namespace Core
