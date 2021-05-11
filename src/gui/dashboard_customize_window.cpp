/**
 * @file
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_customize_window.hpp"

#include <ui_dashboard_customize_window.h>

/**
 * @brief Initializes the customization window
 * @param callerWidget the title of this window will be used as the title edit text
 */
DashboardCustomizeWindow::DashboardCustomizeWindow(QWidget *callerWidget) {
	ui.setupUi(this);

	setWindowTitle("Change window title");

	ui.titleEdit->setText(callerWidget->windowTitle());
	oldTitle = callerWidget->windowTitle();

	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &DashboardCustomizeWindow::close);
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &DashboardCustomizeWindow::confirmChanges);
}

/**
 * @brief Confirm the changes and emit the respective signals if values changed
 * Then close the window
 */
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

/**
 * Set the inital device type string
 * @param initalDeviceType device type
 */
void DashboardCustomizeWindow::setDeviceType(QString initalDeviceType) {
	ui.deviceTypeEdit->setText(initalDeviceType);
	oldDeviceType = initalDeviceType;
}

/**
 * Sets the initial status display length
 * @param initialLength status display length
 */
void DashboardCustomizeWindow::setStatusDisplayLength(int initialLength) {
	ui.statusLenghtSpinBox->setValue(initialLength);
	oldLength = initialLength;
}
