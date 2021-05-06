/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "topic_selection_window.hpp"
TopicSelectionWindow::TopicSelectionWindow() {
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(addNewTopic()));
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(addNewTopic()));
}

void TopicSelectionWindow::addNewTopic() {
	auto item = new QTreeWidgetItem(ui.treeWidget);
	item->setText(0, ui.lineEdit->text());
	ui.lineEdit->selectAll();
}
