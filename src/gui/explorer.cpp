/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer.hpp"

#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>
#include <qdebug.h>

#include "publish_window.hpp"
#include "ui_content_widget.h"

/**
 * @brief Initializes the explorer tab
 */
Explorer::Explorer() {
	ui.setupUi(this);

	ui.timestampWidget->hide();

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

	connect(ui.dashboardButton, SIGNAL(clicked(bool)), this, SLOT(sendDashboardRequest()));
}

/**
 * @brief Setter for data model
 * @param model data model
 */
void Explorer::setDataModel(DataModel *model) {
	dataModel = model;
}

/**
 * @brief Setter for client
 * @param mqttClient mqtt client
 */
void Explorer::setClient(Core::Client *mqttClient) {
	client = mqttClient;
}

/**
 * @brief Connects the explorers dashboard request signal to the receiving dashboard slot
 * @param dashboard receiving dashboard
 */
void Explorer::connectToDashboard(Dashboard *dashboard) {
	connect(this, &Explorer::dashboardRequest, dashboard, &Dashboard::addTopic);
}

/**
 * @brief Sets the new message limit for the explorer and all Topics
 * @note this is buggy and is not used anywhere but may? be part of the specification
 */
void Explorer::setMessageLimit() {
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
 * @brief Updates the last message content view with the selected message payload
 * Can be used after content change to update the content view
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

	ui.timestampLabel->setText(currentItem->getTopic()->getTimestampString());
	ui.timestampWidget->setVisible(ui.timestampLabel->text() != "");
}

/**
 * @brief Hierarchically displays the received message in the explorer
 * @param message MQTT message
 */
void Explorer::receiveMessage(mqtt::const_message_ptr message) {
	QString topic = QString::fromStdString(message->get_topic());
	ExplorerItem *item = findOrCreateItemFromTopic(topic);

	QString payload = QString::fromStdString(message->get_payload());
	item->getTopic()->addPayload(payload);
	updateContentBlock();
}

/**
 * @brief Finds or creates an item with path topic
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
 * @brief Finds or creates an immediate child item
 * @note should be analogous to ExplorerItem::findOrCreateChild
 * @param name name of the item
 * @return pointer to a new or existing item
 */
ExplorerItem *Explorer::findOrCreateRootChild(QString &name) {
	auto rootItems = ui.treeWidget->findItems(name, Qt::MatchExactly, 0);

	ExplorerItem *root;
	if (rootItems.empty()) {
		// adding a new root topic
		root = new ExplorerItem(ui.treeWidget, dataModel->addTopic(name, nullptr));

	} else {
		// root topic found
		root = dynamic_cast<ExplorerItem *>(rootItems.at(0));
	}

	return root;
}

/**
 * @brief Save action
 * Save the explorer hierarchy to a previously used savefile or ask the user for a new file
 */
void Explorer::saveStructure() {
	if (lastSaveDir == "") {
		saveStructureAs();
	} else {
		saveState(lastSaveDir);
	}
}

/**
 * @brief Save As action
 * Ask the user for a save file and save the explorer hierarchy to it
 */
void Explorer::saveStructureAs() {
	QString userDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
														"",
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

/**
 * @brief Does the actual saving
 * Saves the explorer architecture to a JSON file
 * @param directory path to a save directory where the new structure will be created
 */
void Explorer::saveState(const QString &directory) {
	qInfo() << "Saving structure to" << directory;

	for (int i = 0; i < ui.treeWidget->topLevelItemCount(); ++i) {
		auto explorerItem = dynamic_cast<ExplorerItem *>(ui.treeWidget->topLevelItem(i));
		explorerItem->saveSubtree(directory);
	}
}

/**
 * @brief Opens a new publish window (multiple publish windows may be open at the same time)
 * @param item selected item
 * @param column discarded -> only column 0 is used
 */
void Explorer::openPublishWindow(QTreeWidgetItem *item, int column) {
	auto explorerItem = dynamic_cast<ExplorerItem *>(item);

	auto publishWindow = new PublishWindow(explorerItem->getTopic(), client);
	publishWindow->show();
	qDebug() << "Publish window opened for topic" << explorerItem->getTopic()->getName();
}

/**
 * @brief Sends a request to the dashboard with the selected topic
 * A new subwindow will be created from the selected topic
 */
void Explorer::sendDashboardRequest() {
	auto selectedItems = ui.treeWidget->selectedItems();

	if (selectedItems.empty()) {
		return;
	}

	auto currentItem = dynamic_cast<ExplorerItem *>(selectedItems.front());
	emit dashboardRequest(currentItem->getTopic());
}

/**
 * @brief Loads the dashboard from an user selected file
 * This needs to be done in the explorer because for every saved topic we need to create a semi-message
 * which is also stored and which represents the last received message from that topic
 * A new dashboardRequest is then made and the topic is added as a subwindow
 * The new subwindow will load the rest of data from the given QJsonObject
 */
void Explorer::loadDashboard() {
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
													"",
													tr("Dashboard configuration files (*.json)"));

	qInfo() << "Loading dashboard from" << filePath;
	QFile file = QFile(filePath);
	file.open(QIODevice::ReadOnly);

	if (!file.isOpen()) {
		qWarning() << "Can't open dashboard file for reading";
		return;
	}

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	QJsonArray dataArray = doc["data"].toArray();

	for (auto item : dataArray) {
		QJsonObject itemObject = item.toObject();

		QString topic = itemObject["topic"].toString();
		ExplorerItem *explorerItem = findOrCreateItemFromTopic(topic);

		QString payload = itemObject["last_payload"].toString();
		explorerItem->getTopic()->addPayload(payload);
		updateContentBlock();

		emit dashboardRequest(explorerItem->getTopic(), new QJsonObject(itemObject));
	}

	file.close();
}
