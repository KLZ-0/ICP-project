/**
 * @file
 * @author Adrián Kálazi (xkalaz00)
 */

#include "topic_selection_window.hpp"

/**
 * Initializes a new topic selection window
 * @param topics initial topics
 */
TopicSelectionWindow::TopicSelectionWindow(const QSet<QString> &topics) {
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	for (const QString &topic : topics) {
		addNewTopic(topic);
	}

	connect(ui.addButton, SIGNAL(clicked(bool)), this, SLOT(addNewTopic()));
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(addNewTopic()));
	connect(ui.removeButton, SIGNAL(clicked(bool)), this, SLOT(removeSelectedTopic()));
	connect(ui.saveButton, SIGNAL(clicked(bool)), this, SLOT(confirmChanges()));

	connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, ui.treeWidget, &QTreeWidget::editItem);
	connect(ui.treeWidget, &QTreeWidget::itemChanged, this, &TopicSelectionWindow::checkForDuplicates);
}

/**
 * Adds new topics to the treewidget
 * @param topic
 */
void TopicSelectionWindow::addNewTopic(QString topic) {
	if (topic == nullptr) {
		topic = ui.lineEdit->text();
	}

	QTreeWidgetItem *item;

	auto search_items = ui.treeWidget->findItems(topic, Qt::MatchExactly, 0);
	if (search_items.empty()) {
		item = new QTreeWidgetItem(ui.treeWidget);
	} else {
		item = search_items.at(0);
	}

	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	item->setText(0, topic);
	ui.lineEdit->selectAll();
}

/**
 * Removes the selected topic from the treewidget
 */
void TopicSelectionWindow::removeSelectedTopic() {
	if (ui.treeWidget->selectedItems().empty()) {
		return;
	}

	QTreeWidgetItem *selectedItem = ui.treeWidget->selectedItems().at(0);
	delete selectedItem;
}

/**
 * Performs a duplicate check which ensures that only one of each topic will be in the list
 * @param item item which changed
 * @param column should always be 0
 */
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

/**
 * Confirms the changes and emits the topicsSelected signal before closing
 */
void TopicSelectionWindow::confirmChanges() {
	QSet<QString> topics;

	for (int i = 0; i < ui.treeWidget->topLevelItemCount(); ++i) {
		topics.insert(ui.treeWidget->topLevelItem(i)->text(0));
	}

	emit topicsSelected(topics);
	close();
}
