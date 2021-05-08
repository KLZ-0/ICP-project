/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "dashboard_customize_window.hpp"

DashboardCustomizeWindow::DashboardCustomizeWindow(QWidget *callerWidget) {
	ui.setupUi(this);

	setWindowTitle("Change window title");

	ui.lineEdit->setText(callerWidget->windowTitle());
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &DashboardCustomizeWindow::close);
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &DashboardCustomizeWindow::confirmNewTile);
	connect(ui.lineEdit, &QLineEdit::returnPressed, this, &DashboardCustomizeWindow::confirmNewTile);
}

void DashboardCustomizeWindow::confirmNewTile() {
	emit titleConfirmed(ui.lineEdit->text());
	close();
}
