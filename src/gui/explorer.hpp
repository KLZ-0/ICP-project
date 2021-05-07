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
	DataModel *dataModel;

	int messageLimit = 3;
	QVector<QPlainTextEdit *> contentEdits;

	ExplorerItem *findOrCreateItemFromTopic(QString &topic);
	ExplorerItem *findOrCreateRootChild(QString &name);

	const int MAX_MESSAGE_RENDER_LENGTH = 300;

public slots:
	void setMessageLimit();
	void updateContentBlock();
	void receiveMessage(mqtt::const_message_ptr message);
};


#endif //MQTT_EXPLORER_EXPLORER_HPP
