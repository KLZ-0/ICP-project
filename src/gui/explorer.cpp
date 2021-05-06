/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer.hpp"

#include <iostream>

Explorer::Explorer() {
	ui.setupUi(this);

	auto item = new ExplorerItem(ui.treeWidget, messageLimit);
	item->setText(0, "top level item");
	item->addPayload("data1");

	auto subItem = new ExplorerItem(item, messageLimit);
	subItem->setText(0, "lower level item");
	subItem->addPayload("data2");

	auto subsubItem = new ExplorerItem(subItem, messageLimit);
	subsubItem->setText(0, "even lower level item");
	subsubItem->addPayload("data3");

	connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &Explorer::updateContentBlock);

	// TODO: dummy
	connect(ui.dummyButton, SIGNAL(clicked(bool)), this, SLOT(dummyCallback()));
	connect(ui.dummyEdit, SIGNAL(returnPressed()), this, SLOT(dummyCallback()));
}

/**
 * Updates the last message content view with the message payload
 * @param tree_item tree item from which the payload should be loaded
 * @param column always 0
 */
void Explorer::updateContentBlock(QTreeWidgetItem *tree_item, int column) {
	auto item = dynamic_cast<ExplorerItem *>(tree_item);

	ui.plainTextEdit->setPlainText(item->getPayload());
}

/**
 * Hierarchically displays the received message in the explorer
 * @param message MQTT message
 */
void Explorer::receiveMessage(mqtt::message &message) {
	QString topic = QString::fromStdString(message.get_topic());
	ExplorerItem *item = findOrCreateItemFromTopic(topic);

	// TODO: probably use message.get_payload()
	item->incrementMessageCount();
	item->addPayload(QString::fromStdString(message.get_payload_str()));
}

/**
 * Finds or creates an item with path topic
 * Also creates sub-level items if they don't exist
 * @param topic topic path string (e.g. "/topic/subtopic/subsubtopic")
 * @return item to which a payload can be attached
 */
ExplorerItem *Explorer::findOrCreateItemFromTopic(QString &topic) {
	ExplorerItem *root = nullptr;
	for (QString &subtopic : topic.split("/")) {
		if (root == nullptr) {
			root = findOrCreateRootChild(subtopic);
		} else {
			root = root->findOrCreateChild(subtopic);
		}
	}

	return root;
}

/**
 * Finds or creates an immediate child item
 * @note should be analogous to ExplorerItem::findOrCreateChild
 * @param name name of the item
 * @return pointer to a new or existing item
 */
ExplorerItem *Explorer::findOrCreateRootChild(QString &name) {
	auto rootItems = ui.treeWidget->findItems(name, Qt::MatchExactly, 0);

	ExplorerItem *root;
	if (rootItems.empty()) {
		// adding a new root topic
		root = new ExplorerItem(ui.treeWidget, messageLimit);
		root->setText(0, name);
	} else {
		// root topic found
		root = dynamic_cast<ExplorerItem *>(rootItems.at(0));
	}

	return root;
}

void Explorer::dummyCallback() {
	mqtt::message message;

	message.set_topic(ui.dummyEdit->text().toUtf8().data());
	message.set_payload(std::to_string(dummyCount++).c_str());

	receiveMessage(message);
}
