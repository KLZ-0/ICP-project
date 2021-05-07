/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "data_model.hpp"

#include <QDebug>

DataModel::DataModel(int messageLimit) {
	limit = messageLimit;
}

Topic *DataModel::addTopic(QString &name) {
	auto topic = new Topic(name, limit);
	topics.append(topic);
	return topic;
}

void DataModel::setTopicMessageLimit(int newLimit) {
	for (Topic *topic : topics) {
		topic->setMessageLimit(limit);
	}
	limit = newLimit;
}

DataModel::~DataModel() {
	for (Topic *topic : topics) {
		delete topic;
	}
}
