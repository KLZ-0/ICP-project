/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard.hpp"

#include "dashboard_item.hpp"
Dashboard::Dashboard() {
	ui.setupUi(this);

	ui.mdiArea->addSubWindow(new DashboardItem);
	ui.mdiArea->addSubWindow(new DashboardItem("very nice!!!"));
	ui.mdiArea->addSubWindow(new DashboardItem("another subwindow"));
}
