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
