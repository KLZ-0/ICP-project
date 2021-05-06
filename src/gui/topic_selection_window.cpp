/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "topic_selection_window.hpp"
TopicSelectionWindow::TopicSelectionWindow() {
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(addNewTopic()));
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(addNewTopic()));
	connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, ui.treeWidget, &QTreeWidget::editItem);
	connect(ui.treeWidget, &QTreeWidget::itemChanged, this, &TopicSelectionWindow::checkForDuplicates);
}

void TopicSelectionWindow::addNewTopic() {
	QString topic = ui.lineEdit->text();
	QTreeWidgetItem *item;

	auto search_items = ui.treeWidget->findItems(topic, Qt::MatchExactly, 0);
	if (search_items.empty()) {
		item = new QTreeWidgetItem(ui.treeWidget);
	} else {
		item = search_items[0];
	}

	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	item->setText(0, topic);
	ui.lineEdit->selectAll();
}
void TopicSelectionWindow::checkForDuplicates(QTreeWidgetItem *item, int column) {
	// skip duplicates in other oclumns
	if (column != 0) {
		return;
	}

	// if another item with the same topic exists, delete it
	auto search_items = ui.treeWidget->findItems(item->text(0), Qt::MatchExactly, 0);
	if (search_items.size() > 1) {
		for (QTreeWidgetItem *widget_item : search_items) {
			if (widget_item != item) {
				delete widget_item;
			}
		}
	}
}
