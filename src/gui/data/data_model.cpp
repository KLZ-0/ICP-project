/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "data_model.hpp"

#include <QDebug>

/**
 * @brief Initializes the data model
 * @param messageLimit initial message limit
 */
DataModel::DataModel(int messageLimit) {
	limit = messageLimit;
}

/**
 * @brief Creates a new topic
 * The new topic pointer will be stored and freed on datamodel destruction
 * @param name name of the topic
 * @param parentTopic parent topic of the new topic, null if root topic - will be used to acquire the fully qualified name
 * @return pointer to a newly created topic
 */
Topic *DataModel::addTopic(QString &name, Topic *parentTopic) {
	auto topic = new Topic(name, limit, parentTopic);
	topics.append(topic);
	return topic;
}

/**
 * @brief Sets the message limit of all topics (max history)
 * @param newLimit new message limit
 */
void DataModel::setTopicMessageLimit(int newLimit) {
	for (Topic *topic : topics) {
		topic->setMessageLimit(newLimit);
	}
	limit = newLimit;
}

/**
 * @brief Destructs the datamodel
 * Also frees the created topics
 */
DataModel::~DataModel() {
	for (Topic *topic : topics) {
		delete topic;
	}
}
