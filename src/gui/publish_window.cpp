/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "publish_window.hpp"

PublishWindow::PublishWindow(Topic *initialTopic) {
	topic = initialTopic;

	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	ui.lineEdit->setText(topic->getName());
	ui.plainTextEdit->setPlainText(topic->getPayload(0));
}
