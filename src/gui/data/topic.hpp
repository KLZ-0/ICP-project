/**
 * @file
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_TOPIC_HPP
#define MQTT_EXPLORER_TOPIC_HPP

#include <QObject>
#include <ctime>

/**
 * @class Topic
 * @brief Represents a message topic
 * Holds a specified number of payloads as topic history
 * Shared by explorer items and dashboard items
 */
class Topic : public QObject
{
	Q_OBJECT

public:
	explicit Topic(QString &name, int messageLimit, Topic *parentTopic);

	void addPayload(const QString &new_payload);
	QString getPayload(int index);
	std::time_t getTimestamp();
	QString getTimestampString();


	int messageCount() const;
	void setMessageLimit(int messageLimit);
	void setTimestamp(std::time_t newTimeStamp);

	QString getName();
	Topic *getParent();
	QString findFullyQualifiedTopic();

private:
	Topic *parent;
	QString name;
	int limit;                         ///< message limit
	int count = 0;                     ///< message count for this topic
	QVarLengthArray<QString> payloads; ///< last message payload for this topic
	std::time_t lastTimestamp = 0;

signals:
	void changed();
};


#endif //MQTT_EXPLORER_TOPIC_HPP
