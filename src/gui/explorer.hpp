/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_EXPLORER_HPP
#define MQTT_EXPLORER_EXPLORER_HPP


#include <mqtt/message.h>
#include <QPlainTextEdit>
#include <QWidget>

#include "data_model.hpp"
#include "explorer_item.hpp"
#include "ui_explorer.h"

class Explorer : public QWidget
{
	Q_OBJECT

public:
	Explorer();
	void setDataModel(DataModel *model);

private:
	Ui::Explorer ui;
	int dummyCount = 0;
	DataModel *dataModel;

	int messageLimit = 3;
	QVector<QPlainTextEdit *> contentEdits;
	ExplorerItem *currentItem = nullptr;

	ExplorerItem *findOrCreateItemFromTopic(QString &topic);
	ExplorerItem *findOrCreateRootChild(QString &name);

public slots:
	void setMessageLimit();
	void updateContentBlock();

private slots:
	void updateContentBlockFromItem(QTreeWidgetItem *tree_item, int column);
	void receiveMessage(mqtt::message &message);
	void dummyCallback();
};


#endif //MQTT_EXPLORER_EXPLORER_HPP
