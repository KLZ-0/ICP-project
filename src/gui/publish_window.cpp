/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "publish_window.hpp"

#include <QDebug>

PublishWindow::PublishWindow(Topic *initialTopic, Core::Client *mqttClient) {
	client = mqttClient;

	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	if (initialTopic != nullptr) {
		ui.lineEdit->setText(initialTopic->findFullyQualifiedTopic());
		ui.plainTextEdit->setPlainText(initialTopic->getPayload(0));
	}

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
