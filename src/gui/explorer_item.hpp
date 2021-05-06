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

private:
	QString payload;
};


#endif //MQTT_EXPLORER_EXPLORER_ITEM_HPP
