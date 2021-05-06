/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer_item.hpp"

ExplorerItem::ExplorerItem(QTreeWidget *treeview)
	: QTreeWidgetItem(treeview) {
}

ExplorerItem::ExplorerItem(QTreeWidgetItem *parent)
	: QTreeWidgetItem(parent) {
}

void ExplorerItem::setPayload(QString &&new_payload) {
	payload = new_payload;
}
QString &ExplorerItem::getPayload() {
	return payload;
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

ExplorerItem *ExplorerItem::findOrCreateChild(QString &name) {
	for (int i = 0; i < childCount(); i++) {
		QTreeWidgetItem *item = child(i);
		if (item->text(0) == name) {
			return dynamic_cast<ExplorerItem *>(item);
		}
	}

	auto item = new ExplorerItem(this);
	item->setText(0, name);
	return item;
}
