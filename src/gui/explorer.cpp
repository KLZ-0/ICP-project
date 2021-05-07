/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer.hpp"

#include <QFileDialog>
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

	connect(ui.treeWidget, &QTreeWidget::itemSelectionChanged, this, &Explorer::updateContentBlock);
	connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, &Explorer::openPublishWindow);
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
 * Updates the last message content view with the selected message payload
 * Could be used after content change to update the content view
 */
void Explorer::updateContentBlock() {
	auto selectedItems = ui.treeWidget->selectedItems();

	if (selectedItems.empty()) {
		return;
	}

	auto currentItem = dynamic_cast<ExplorerItem *>(selectedItems.front());
	for (int i = 0; i < messageLimit; i++) {
		QString payload = currentItem->getTopic()->getPayload(i);
		payload.truncate(MAX_MESSAGE_RENDER_LENGTH);
		ui.tabWidget->setTabVisible(i, payload != "");
		contentEdits.at(i)->setPlainText(payload);
	}
}

/**
 * Hierarchically displays the received message in the explorer
 * @param message MQTT message
 */
void Explorer::receiveMessage(mqtt::const_message_ptr message) {
	QString topic = QString::fromStdString(message->get_topic());
	ExplorerItem *item = findOrCreateItemFromTopic(topic);

	// TODO: probably use message.get_payload()
	QString payload = QString::fromStdString(message->get_payload());
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

void Explorer::saveStructure() {
	if (lastSaveDir == "") {
		saveStructureAs();
	} else {
		saveState(lastSaveDir);
	}
}

void Explorer::saveStructureAs() {
	QString userDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
														"/home",
														QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (userDir == "") {
		return;
	}

	QDir dir(userDir);
	if (!dir.exists()) {
		return;
	}

	saveState(userDir);

	lastSaveDir = userDir;
}

void Explorer::saveState(const QString &directory) {
	qInfo() << "Saving structure to" << directory;

	for (int i = 0; i < ui.treeWidget->topLevelItemCount(); ++i) {
		auto explorerItem = dynamic_cast<ExplorerItem *>(ui.treeWidget->topLevelItem(i));
		explorerItem->saveSubtree(directory);
	}
}

void Explorer::openPublishWindow(QTreeWidgetItem *item, int column) {
	auto explorerItem = dynamic_cast<ExplorerItem *>(item);
	qDebug() << "Publish window opened for topic" << explorerItem->getTopic()->getName();
}
