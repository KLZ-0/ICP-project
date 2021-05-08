/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "explorer_item.hpp"

#include <QDebug>
#include <QDir>
#include <fstream>

/**
 * @brief Initializes a new root item
 * @param treeview parent tree widget
 * @param topic item topic
 */
ExplorerItem::ExplorerItem(QTreeWidget *treeview, Topic *topic)
	: QTreeWidgetItem(treeview) {
	this->topic = topic;
	setText(0, topic->getName());
}

/**
 * @brief Initializes a new non-root item
 * @param parent parent tree item
 * @param topic item topic
 */
ExplorerItem::ExplorerItem(QTreeWidgetItem *parent, Topic *topic)
	: QTreeWidgetItem(parent) {
	this->topic = topic;
	setText(0, topic->getName());
}

/**
 * @brief Finds or creates an immediate child item
 * @note should be analogous to Explorer::findOrCreateRootChild
 * @param name name of the item
 * @param model datamodel from which to query a new topic
 * @return pointer to a new or existing item
 */
ExplorerItem *ExplorerItem::findOrCreateChild(QString &name, DataModel *model) {
	for (int i = 0; i < childCount(); i++) {
		QTreeWidgetItem *item = child(i);
		if (item->text(0) == name) {
			return dynamic_cast<ExplorerItem *>(item);
		}
	}

	auto item = new ExplorerItem(this, model->addTopic(name, this->topic));
	item->setText(0, name);
	return item;
}

/**
 * @brief Getter for topic
 * @return item topic
 */
Topic *ExplorerItem::getTopic() {
	return topic;
}

/**
 * @brief Saves the subtree of this topic
 * Creates a directory for this topic, stores the payload and for every children calls the same method
 * @param parents parent path (absolute path) to the parent directory of this topic
 */
void ExplorerItem::saveSubtree(const QString &parents) {
	QString newParent = parents + "/" + topic->getName();

	QDir dir(newParent);
	dir.mkpath(newParent);
	qDebug() << "mkdir" << newParent;

	if (topic->getPayload(0) != "") {
		qDebug() << "Saving to" << newParent + "/payload.txt";
		std::ofstream payloadFile;
		payloadFile.open((newParent + "/payload.txt").toStdString(), std::ios_base::out | std::ios_base::binary);
		if (payloadFile.is_open()) {
			payloadFile << getTopic()->getPayload(0).toStdString();
			payloadFile.close();
		} else {
			qDebug() << "Failed to open file";
		}
	}

	for (int i = 0; i < childCount(); ++i) {
		auto explorerItem = dynamic_cast<ExplorerItem *>(child(i));
		explorerItem->saveSubtree(newParent);
	}
}
