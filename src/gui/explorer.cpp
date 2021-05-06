/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer.hpp"

#include <iostream>
Explorer::Explorer() {
	ui.setupUi(this);

	auto item = new QTreeWidgetItem(ui.treeWidget);
	item->setText(0, "top level item");

	auto subItem = new QTreeWidgetItem(item);
	subItem->setText(0, "lower level item");

	auto subsubItem = new QTreeWidgetItem(subItem);
	subsubItem->setText(0, "even lower level item");

	connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &Explorer::setContent);
}

void Explorer::setContent(QTreeWidgetItem *item, int column) {
	ui.plainTextEdit->setPlainText(item->text(column));
}
