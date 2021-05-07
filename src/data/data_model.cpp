/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "data_model.hpp"

DataModel::DataModel(int messageLimit) {
	limit = messageLimit;
}

void DataModel::addTopic(QString &name) {
	topics.append(new Topic(name, limit));
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
