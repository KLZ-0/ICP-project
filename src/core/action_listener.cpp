/**
 * @author Kevin Lackó (xlacko08)
 */


#include "action_listener.hpp"

#include <mqtt/token.h>
#include <qdebug.h>

#include "client.hpp"

namespace Core
{
	ActionListener::ActionListener(Client *caller)
		: sig_(caller) {
	}
	void ActionListener::on_success(const mqtt::token &tok) {
		if (tok.get_message_id() != 0)
			qDebug() << "Success for token: [" << tok.get_message_id() << "]";
		auto top = tok.get_topics();
		if (top && !top->empty())
			qDebug() << "\ttoken topic: '" << (*top)[0].c_str() << "', ...";
		qDebug() << "\n";
		emit sig_->ActionSucceeded(tok);
	}
	void ActionListener::on_failure(const mqtt::token &tok) {
		if (tok.get_message_id() != 0)
			qDebug() << "Failure for token: [" << tok.get_message_id() << "]";
		qDebug() << "\n";
		emit sig_->ActionFailed(tok);
	}
} // namespace Core
