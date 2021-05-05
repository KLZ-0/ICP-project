/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_item.hpp"

DashboardItem::DashboardItem() {
	ui.setupUi(this);
}

DashboardItem::DashboardItem(QString content) {
	ui.setupUi(this);

	ui.label->setText(content);
}
