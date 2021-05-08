/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_EXPLORER_ITEM_HPP
#define MQTT_EXPLORER_EXPLORER_ITEM_HPP

#include <QTreeWidgetItem>

#include "data_model.hpp"
#include "topic.hpp"

/**
 * @class ExplorerItem
 * @brief Represents one topic as an item in the explorer hierarchy
 * Not to be confused with Topic, which holds the payload and topic name, this class is only for the UI representation of topics
 * On save, the UI structure is saved and only the name and payload of the Topic is used
 */
class ExplorerItem : public QTreeWidgetItem
{
public:
	explicit ExplorerItem(QTreeWidget *treeview, Topic *topic);
	explicit ExplorerItem(QTreeWidgetItem *parent, Topic *topic);

	ExplorerItem *findOrCreateChild(QString &name, DataModel *model);
	Topic *getTopic();

	void saveSubtree(const QString &parents);

private:
	Topic *topic;
};


#endif //MQTT_EXPLORER_EXPLORER_ITEM_HPP
