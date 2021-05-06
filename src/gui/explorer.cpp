/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer.hpp"

#include <iostream>

#include "explorer_item.hpp"
Explorer::Explorer() {
	ui.setupUi(this);

	auto item = new ExplorerItem(ui.treeWidget);
	item->setText(0, "top level item");
	item->setPayload("data1");

	auto subItem = new ExplorerItem(item);
	subItem->setText(0, "lower level item");
	subItem->setPayload("data2");

	auto subsubItem = new ExplorerItem(subItem);
	subsubItem->setText(0, "even lower level item");
	subsubItem->setPayload("data3");

	connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &Explorer::setContent);
}

void Explorer::setContent(QTreeWidgetItem *tree_item, int column) {
	auto item = dynamic_cast<ExplorerItem *>(tree_item);

	ui.plainTextEdit->setPlainText(item->getPayload());
}
