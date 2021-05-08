/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "topic.hpp"

#include <QDebug>

Topic::Topic(QString &name, int messageLimit, Topic *parentTopic) {
	this->name = name;
	limit = messageLimit;
	parent = parentTopic;
}

void Topic::addPayload(const QString &new_payload) {
	if (count >= limit) {
		payloads.resize(limit - 1);
	}
	payloads.insert(0, new_payload);
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

Topic *Topic::getParent() {
	return parent;
}

QString Topic::getFullyQualifiedTopic() {
	QString topicString = this->getName();

	Topic *tmp_parent = this->getParent();
	while (tmp_parent != nullptr) {
		topicString = tmp_parent->getName() + "/" + topicString;
		tmp_parent = tmp_parent->getParent();
	}

	return topicString;
}
