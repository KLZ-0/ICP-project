/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_item.hpp"

#include <QDebug>
#include <QMenu>

#include "title_selection_window.hpp"

DashboardItem::DashboardItem(QWidget *parent, Topic *widgetTopic)
	: QMdiSubWindow(parent) {
	topic = widgetTopic;

	auto contentWidget = new QWidget(this);
	ui.setupUi(contentWidget);
	setWidget(contentWidget);

	setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle(widgetTopic->getName());
	ui.label->setText(widgetTopic->findFullyQualifiedTopic());
	connect(topic, &Topic::changed, this, &DashboardItem::updateContent);

	auto changeTitleAction = new QAction("Change title");
	connect(changeTitleAction, SIGNAL(triggered(bool)), this, SLOT(openTitleSelectionWindow()));

	QMenu *menu = systemMenu();
	menu->addAction(changeTitleAction);
}

void DashboardItem::openTitleSelectionWindow() {
	auto titleWindow = new TitleSelectionWindow(this);
	connect(titleWindow, &TitleSelectionWindow::titleConfirmed, this, &DashboardItem::setWindowTitle);
	titleWindow->show();
}

void DashboardItem::updateContent() {
	qDebug() << "Update dashboard item";
}
