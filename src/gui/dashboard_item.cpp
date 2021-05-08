/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_item.hpp"

#include <QMenu>

#include "title_selection_window.hpp"

DashboardItem::DashboardItem(QWidget *parent, Topic *widgetTopic)
	: QMdiSubWindow(parent) {
	auto contentWidget = new QWidget(this);
	ui.setupUi(contentWidget);
	setWidget(contentWidget);

	setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle(widgetTopic->getName());
	ui.label->setText(widgetTopic->findFullyQualifiedTopic());

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
