/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_MAIN_WINDOW_HPP
#define MQTT_EXPLORER_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QPlainTextEdit>

#include "ui_main_window.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private:
	Ui::MainWindow ui;
};


#endif //MQTT_EXPLORER_MAIN_WINDOW_HPP
