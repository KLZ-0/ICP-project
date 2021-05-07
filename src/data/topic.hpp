/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_TOPIC_HPP
#define MQTT_EXPLORER_TOPIC_HPP

#include <QObject>

class Topic : QObject
{
	Q_OBJECT

public:
	explicit Topic(QString &name, int messageLimit);

	void addPayload(QString &&new_payload);
	QString getPayload(int index);

	int messageCount() const;
	void setMessageLimit(int messageLimit);

private:
	QString name;
	int limit;                 ///< message limit
	int count = 0;             ///< message count for this topic
	QVector<QString> payloads; ///< last message payload for this topic

signals:
	void changed(Topic *topic);
};


#endif //MQTT_EXPLORER_TOPIC_HPP
