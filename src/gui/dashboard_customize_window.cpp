/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_customize_window.hpp"

#include <ui_dashboard_customize_window.h>

DashboardCustomizeWindow::DashboardCustomizeWindow(QWidget *callerWidget) {
	ui.setupUi(this);

	setWindowTitle("Change window title");

	ui.titleEdit->setText(callerWidget->windowTitle());
	oldTitle = callerWidget->windowTitle();

	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &DashboardCustomizeWindow::close);
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &DashboardCustomizeWindow::confirmChanges);
}

void DashboardCustomizeWindow::confirmChanges() {
	const QString &newTitle = ui.titleEdit->text();
	if (newTitle != oldTitle && newTitle != "") {
		emit titleChanged(newTitle);
	}

	const QString &newDeviceType = ui.deviceTypeEdit->text();
	if (newDeviceType != oldDeviceType) {
		emit deviceTypeChanged(newDeviceType);
	}

	int newLength = ui.statusLenghtSpinBox->value();
	if (newLength != oldLength) {
		emit statusDisplayLengthChanged(newLength);
	}

	close();
}

void DashboardCustomizeWindow::setDeviceType(QString initalDeviceType) {
	ui.deviceTypeEdit->setText(initalDeviceType);
	oldDeviceType = initalDeviceType;
}

void DashboardCustomizeWindow::setStatusDisplayLength(int initialLength) {
	ui.statusLenghtSpinBox->setValue(initialLength);
	oldLength = initialLength;
}
