/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_TITLE_SELECTION_WINDOW_HPP
#define MQTT_EXPLORER_TITLE_SELECTION_WINDOW_HPP

#include <QWidget>

#include "ui_title_selection_window.h"

class TitleSelectionWindow : public QWidget
{
	Q_OBJECT
public:
	explicit TitleSelectionWindow(QWidget *callerWidget);

private:
	Ui::TitleSelectionWindow ui;

signals:
	void titleConfirmed(QString newTitle);

private slots:
	void confirmNewTile();
};


#endif //MQTT_EXPLORER_TITLE_SELECTION_WINDOW_HPP
