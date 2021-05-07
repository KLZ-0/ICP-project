/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "publish_window.hpp"

#include <QDebug>

PublishWindow::PublishWindow(Topic *initialTopic) {
	topic = initialTopic;

	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	ui.lineEdit->setText(topic->getName());
	ui.plainTextEdit->setPlainText(topic->getPayload(0));

	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &PublishWindow::close);
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &PublishWindow::sendMessage);
}

void PublishWindow::sendMessage() {
	QString send_topic = ui.lineEdit->text();
	QString send_payload = ui.plainTextEdit->toPlainText();

	qDebug() << send_topic << send_payload;
	close();
}
