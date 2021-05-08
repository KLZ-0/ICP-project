/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_customize_window.hpp"

#include <ui_dashboard_customize_window.h>

DashboardCustomizeWindow::DashboardCustomizeWindow(QWidget *callerWidget) {
	ui.setupUi(this);

	setWindowTitle("Change window title");

	ui.titleEdit->setText(callerWidget->windowTitle());
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &DashboardCustomizeWindow::close);
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &DashboardCustomizeWindow::confirmChanges);
}

void DashboardCustomizeWindow::confirmChanges() {
	emit titleChanged(ui.titleEdit->text());
	emit deviceTypeChanged(ui.deviceTypeEdit->text());
	emit statusDisplayLengthChanged(ui.statusLenghtSpinBox->value());

	close();
}

void DashboardCustomizeWindow::setDeviceType(QString initalDeviceType) {
	ui.deviceTypeEdit->setText(initalDeviceType);
}

void DashboardCustomizeWindow::setStatusDisplayLength(int initialLength) {
	ui.statusLenghtSpinBox->setValue(initialLength);
}
