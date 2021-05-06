/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_EXPLORER_ITEM_HPP
#define MQTT_EXPLORER_EXPLORER_ITEM_HPP

#include <QTreeWidgetItem>
/**
 * Represents one topic as an item in the explorer QTreeWidget
 */
class ExplorerItem : public QTreeWidgetItem
{
public:
	explicit ExplorerItem(QTreeWidget *treeview, int messageLimit);
	explicit ExplorerItem(QTreeWidgetItem *parent, int messageLimit);

	void addPayload(QString &&new_payload);
	QString getPayload(int index);
	int payloadCount();

	void incrementMessageCount();
	void setMessageCount(int messageCount);
	int messageCount() const;

	ExplorerItem *findOrCreateChild(QString &name);

private:
	int limit;
	int count = 0;             ///< message count for this topic
	QVector<QString> payloads; ///< last message payload for this topic
};


#endif //MQTT_EXPLORER_EXPLORER_ITEM_HPP
