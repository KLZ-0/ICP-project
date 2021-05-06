/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer_item.hpp"

ExplorerItem::ExplorerItem(QTreeWidget *treeview, int messageLimit)
	: QTreeWidgetItem(treeview) {
	limit = messageLimit;
	payloads.reserve(messageLimit);
}

ExplorerItem::ExplorerItem(QTreeWidgetItem *parent, int messageLimit)
	: QTreeWidgetItem(parent) {
	limit = messageLimit;
	payloads.reserve(messageLimit);
}

void ExplorerItem::addPayload(QString &&new_payload) {
	if (count > limit) {
		payloads.removeLast();
	}
	payloads.push_front(new_payload);
}

QString ExplorerItem::getPayload(int index) {
	if (index < payloads.size()) {
		return payloads.at(index);
	} else {
		return "";
	}
}

void ExplorerItem::incrementMessageCount() {
	count++;
}

void ExplorerItem::setMessageCount(int messageCount) {
	count = messageCount;
}

int ExplorerItem::messageCount() const {
	return count;
}

/**
 * Finds or creates an immediate child item
 * @note should be analogous to Explorer::findOrCreateRootChild
 * @param name name of the item
 * @return pointer to a new or existing item
 */
ExplorerItem *ExplorerItem::findOrCreateChild(QString &name) {
	for (int i = 0; i < childCount(); i++) {
		QTreeWidgetItem *item = child(i);
		if (item->text(0) == name) {
			return dynamic_cast<ExplorerItem *>(item);
		}
	}

	auto item = new ExplorerItem(this, this->limit);
	item->setText(0, name);
	return item;
}
