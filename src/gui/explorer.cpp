/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer.hpp"

#include <iostream>
#include <qdebug.h>

#include "ui_content_widget.h"

Explorer::Explorer() {
	ui.setupUi(this);

	for (int i = 0; i < messageLimit; ++i) {
		auto widget = new QWidget;
		Ui::ContentWidget content_ui;
		content_ui.setupUi(widget);

		ui.tabWidget->addTab(widget, QString::fromStdString(std::to_string(i + 1)));
		ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(widget), false);

		contentEdits.append(content_ui.plainTextEdit);
	}

	connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &Explorer::updateContentBlockFromItem);

	// TODO: dummy
	connect(ui.dummyButton, SIGNAL(clicked(bool)), this, SLOT(dummyCallback()));
	connect(ui.dummyEdit, SIGNAL(returnPressed()), this, SLOT(dummyCallback()));
}

void Explorer::setDataModel(DataModel *model) {
	dataModel = model;
}

void Explorer::setMessageLimit() {
	// TODO: fix this shit
	int limit = 4;

	if (limit == messageLimit) {
		return;
	} else if (limit > messageLimit) {
		for (int i = messageLimit; i < limit; ++i) {
			auto widget = new QWidget;
			Ui::ContentWidget content_ui;
			content_ui.setupUi(widget);

			ui.tabWidget->addTab(widget, QString::fromStdString(std::to_string(i + 1)));
			ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(widget), false);

			contentEdits.insert(i, content_ui.plainTextEdit);
		}
	} else {
		for (int i = messageLimit - 1; i >= limit; --i) {
			ui.tabWidget->removeTab(i);
		}
		contentEdits.resize(limit);
	}

	dataModel->setTopicMessageLimit(limit);

	messageLimit = limit;
}

/**
 * Updates the last message content view with the last message payload
 * Could be used after content change to update the content view
 */
void Explorer::updateContentBlock() {
	if (currentItem == nullptr) {
		return;
	}

	for (int i = 0; i < messageLimit; i++) {
		QString payload = currentItem->getTopic()->getPayload(i);
		ui.tabWidget->setTabVisible(i, payload != "");
		contentEdits.at(i)->setPlainText(payload);
	}
}

/**
 * Updates the last message content view with the message payload
 * @param tree_item tree item from which the payload should be loaded
 * @param column always 0
 */
void Explorer::updateContentBlockFromItem(QTreeWidgetItem *tree_item, int column) {
	currentItem = dynamic_cast<ExplorerItem *>(tree_item);
	updateContentBlock();
}

/**
 * Hierarchically displays the received message in the explorer
 * @param message MQTT message
 */
void Explorer::receiveMessage(mqtt::const_message_ptr message) {
	QString topic = QString::fromStdString(message->get_topic());
	ExplorerItem *item = findOrCreateItemFromTopic(topic);

	// TODO: probably use message.get_payload()
	QString payload = QString::fromStdString(message->get_payload_str());
	item->getTopic()->addPayload(payload);
	updateContentBlock();
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
			root = root->findOrCreateChild(subtopic, dataModel);
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
		root = new ExplorerItem(ui.treeWidget, dataModel->addTopic(name));

	} else {
		// root topic found
		root = dynamic_cast<ExplorerItem *>(rootItems.at(0));
	}

	return root;
}

void Explorer::dummyCallback() {
	//	mqtt::message message;
	//
	//	message.set_topic(ui.dummyEdit->text().toUtf8().data());
	//	message.set_payload(std::to_string(dummyCount++).c_str());
	//
	//	receiveMessage(message);
}
