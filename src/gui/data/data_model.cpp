/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "data_model.hpp"

#include <QDebug>

DataModel::DataModel(int messageLimit) {
	limit = messageLimit;
}

Topic *DataModel::addTopic(QString &name, Topic *parentTopic) {
	auto topic = new Topic(name, limit, parentTopic);
	topics.append(topic);
	return topic;
}

void DataModel::setTopicMessageLimit(int newLimit) {
	for (Topic *topic : topics) {
		topic->setMessageLimit(newLimit);
	}
	limit = newLimit;
}

DataModel::~DataModel() {
	for (Topic *topic : topics) {
		delete topic;
	}
}
