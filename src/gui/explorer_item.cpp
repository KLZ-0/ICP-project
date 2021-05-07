/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer_item.hpp"

ExplorerItem::ExplorerItem(QTreeWidget *treeview, Topic *topic)
	: QTreeWidgetItem(treeview) {
	this->topic = topic;
	setText(0, topic->getName());
}

ExplorerItem::ExplorerItem(QTreeWidgetItem *parent, Topic *topic)
	: QTreeWidgetItem(parent) {
	this->topic = topic;
	setText(0, topic->getName());
}

/**
 * Finds or creates an immediate child item
 * @note should be analogous to Explorer::findOrCreateRootChild
 * @param name name of the item
 * @return pointer to a new or existing item
 */
ExplorerItem *ExplorerItem::findOrCreateChild(QString &name, DataModel *model) {
	for (int i = 0; i < childCount(); i++) {
		QTreeWidgetItem *item = child(i);
		if (item->text(0) == name) {
			return dynamic_cast<ExplorerItem *>(item);
		}
	}

	auto item = new ExplorerItem(this, model->addTopic(name));
	item->setText(0, name);
	return item;
}

Topic *ExplorerItem::getTopic() {
	return topic;
}
