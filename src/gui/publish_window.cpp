/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "publish_window.hpp"

#include <QDebug>

PublishWindow::PublishWindow(Topic *initialTopic, Core::Client *mqttClient) {
	topic = initialTopic;
	client = mqttClient;

	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	QString topicString = topic->getName();
	Topic *parent = topic->getParent();
	while (parent != nullptr) {
		topicString = parent->getName() + "/" + topicString;
		parent = parent->getParent();
	}

	ui.lineEdit->setText(topicString);
	ui.plainTextEdit->setPlainText(topic->getPayload(0));

	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &PublishWindow::close);
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &PublishWindow::sendMessage);
}

void PublishWindow::sendMessage() {
	QString send_topic = ui.lineEdit->text();
	QString send_payload = ui.plainTextEdit->toPlainText();

	mqtt::message_ptr_builder builder;

	builder.topic(send_topic.toStdString());
	builder.payload(send_payload.toStdString());

	client->Publish(builder.finalize());

	qDebug() << "sent" << send_topic << send_payload;
	close();
}
