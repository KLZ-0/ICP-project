/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer.hpp"

#include <iostream>

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

	connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &Explorer::updateContentBlock);

	// TODO: dummy
	connect(ui.dummyButton, SIGNAL(clicked(bool)), this, SLOT(dummyCallback()));
}

void Explorer::updateContentBlock(QTreeWidgetItem *tree_item, int column) {
	auto item = dynamic_cast<ExplorerItem *>(tree_item);

	ui.plainTextEdit->setPlainText(item->getPayload());
}

void Explorer::receiveMessage(mqtt::message &message) {
	QString topic = QString::fromStdString(message.get_topic());
	ExplorerItem *item = findOrCreateItemFromTopic(topic);

	// TODO: probably use message.get_payload()
	item->setPayload(QString::fromStdString(message.get_payload_str()));
}

/**
 * Finds the parent node where the new subtopic should be attached
 * @param topic topic string (e.g. "/topic/subtopic/subsubtopic")
 * @return null if root topic, a valid parent ExplorerItem pointer otherwise
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

ExplorerItem *Explorer::findOrCreateRootChild(QString &name) {
	auto rootItems = ui.treeWidget->findItems(name, Qt::MatchExactly, 0);

	ExplorerItem *root;
	if (rootItems.empty()) {
		// adding a new root topic
		root = new ExplorerItem(ui.treeWidget);
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
