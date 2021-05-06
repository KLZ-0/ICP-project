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
	explicit ExplorerItem(QTreeWidget *treeview);
	explicit ExplorerItem(QTreeWidgetItem *parent);

	void setPayload(QString &&new_payload);
	QString &getPayload();

	void incrementMessageCount();
	void setMessageCount(int messageCount);
	int messageCount() const;

private:
	int count = 0;   ///< message count for this topic
	QString payload; ///< last message payload for this topic
};


#endif //MQTT_EXPLORER_EXPLORER_ITEM_HPP
