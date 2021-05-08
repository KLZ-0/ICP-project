/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_item.hpp"

DashboardItem::DashboardItem(QWidget *parent, Topic *widgetTopic)
	: QMdiSubWindow(parent) {
	auto contentWidget = new QWidget(this);
	ui.setupUi(contentWidget);
	setWidget(contentWidget);

	setAttribute(Qt::WA_DeleteOnClose);

	setWindowTitle(widgetTopic->getName());
	ui.label->setText(widgetTopic->findFullyQualifiedTopic());
}
