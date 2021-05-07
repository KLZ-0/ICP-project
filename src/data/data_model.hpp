/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_DATA_MODEL_HPP
#define MQTT_EXPLORER_DATA_MODEL_HPP

#include <QObject>

#include "topic.hpp"

/**
 * Holds the hierarchical structure of messages
 */
class DataModel : public QObject
{
	Q_OBJECT

public:
	explicit DataModel(int messageLimit);
	~DataModel() override;

	Topic *addTopic(QString &name);
	void setTopicMessageLimit(int newLimit);

private:
	int limit;
	QVector<Topic *> topics;
};


#endif //MQTT_EXPLORER_DATA_MODEL_HPP
