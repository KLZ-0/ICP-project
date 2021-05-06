/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_item.hpp"

DashboardItem::DashboardItem(QWidget *parent, QString content)
	: QWidget(parent) {
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	ui.label->setText(content);
}
