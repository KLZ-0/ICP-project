/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "topic.hpp"

#include <QDebug>

/**
 * @brief Initializes a new topic
 * @param name topic name
 * @param messageLimit topic message limit (max history)
 * @param parentTopic parent topic of the new topic, null if root topic
 */
Topic::Topic(QString &name, int messageLimit, Topic *parentTopic) {
	this->name = name;
	limit = messageLimit;
	parent = parentTopic;
}

/**
 * @brief Adds a new payload (message) to this topic
 * Also removes the oldest payload if the received message count exceeds the limit
 * @param new_payload
 */
void Topic::addPayload(const QString &new_payload) {
	lastTimestamp = std::time(nullptr);

	if (count >= limit) {
		payloads.resize(limit - 1);
	}
	payloads.insert(0, new_payload);
	count++;

	emit changed();
}

/**
 * @brief Acquires a payload (message)
 * @param index index of the payload, 0 being the most recent
 * @return payload as a QString, an empty string on non-existent index
 */
QString Topic::getPayload(int index) {
	if (index < payloads.size()) {
		return payloads.at(index);
	} else {
		return "";
	}
}

/**
 * @brief Getter for the timestamp of the most recent message
 * @return timestamp as std::time_t (long int)
 */
std::time_t Topic::getTimestamp() {
	return lastTimestamp;
}

/**
 * @brief Constructs a formatted string from the timestamp of the most recent message
 * @return
 */
QString Topic::getTimestampString() {
	if (lastTimestamp == 0) {
		return "";
	}

	char mbstr[100];
	if (!std::strftime(mbstr, sizeof(mbstr), "%F %T", std::localtime(&lastTimestamp))) {
		return "";
	}

	return QString(mbstr);
}

/**
 * @brief Count of all messages received in this topic (even if not stored due to limited history)
 * @return message count
 */
int Topic::messageCount() const {
	return count;
}

/**
 * @brief Sets a new message limit (takes effect only on addPayload)
 * @param messageLimit new message limit
 */
void Topic::setMessageLimit(int messageLimit) {
	limit = messageLimit;
}

/**
 * @brief Getter for name
 * @return name
 */
QString Topic::getName() {
	return name;
}

/**
 * Getter for parent topic
 * @return parent topic
 */
Topic *Topic::getParent() {
	return parent;
}

/**
 * @brief Constructs a string representing the fully qualified name using the parent topics
 * This name can be used to uniquely identify topics
 * e.g. a/b/c/d with d being this topic, the children of this topic are not considered
 * @return QString with fully qualified name
 */
QString Topic::findFullyQualifiedTopic() {
	QString topicString = this->getName();

	Topic *tmp_parent = this->getParent();
	while (tmp_parent != nullptr) {
		topicString = tmp_parent->getName() + "/" + topicString;
		tmp_parent = tmp_parent->getParent();
	}

	return topicString;
}

/**
 * @brief Forces the timestamp to the new value
 * Used mainly when loading the dashboard from a file
 * @param newTimeStamp new timestamp as std::time_t (long int)
 */
void Topic::setTimestamp(std::time_t newTimeStamp) {
	lastTimestamp = newTimeStamp;
}
