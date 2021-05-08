/**
 * @author Adrián Kálazi (xkalaz00)
 */

#include "title_selection_window.hpp"

TitleSelectionWindow::TitleSelectionWindow(QWidget *callerWidget) {
	ui.setupUi(this);

	setWindowTitle("Change window title");

	ui.lineEdit->setText(callerWidget->windowTitle());
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &TitleSelectionWindow::close);
	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &TitleSelectionWindow::confirmNewTile);
	connect(ui.lineEdit, &QLineEdit::returnPressed, this, &TitleSelectionWindow::confirmNewTile);
}

void TitleSelectionWindow::confirmNewTile() {
	emit titleConfirmed(ui.lineEdit->text());
	close();
}
