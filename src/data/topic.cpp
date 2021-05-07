/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "topic.hpp"

#include <QDebug>

Topic::Topic(QString &name, int messageLimit) {
	this->name = name;
	limit = messageLimit;
}

void Topic::addPayload(const QString &new_payload) {
	if (count >= limit) {
		payloads.resize(limit - 1);
	}
	payloads.push_front(new_payload);
	count++;

	emit changed(this);
}

QString Topic::getPayload(int index) {
	if (index < payloads.size()) {
		return payloads.at(index);
	} else {
		return "";
	}
}

int Topic::messageCount() const {
	return count;
}

void Topic::setMessageLimit(int messageLimit) {
	limit = messageLimit;
}

QString Topic::getName() {
	return name;
}
