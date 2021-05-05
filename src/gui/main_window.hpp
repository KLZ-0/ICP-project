/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_MAIN_WINDOW_HPP
#define MQTT_EXPLORER_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QPlainTextEdit>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	MainWindow();

private:
	QWidget *mainWidget;
};


#endif //MQTT_EXPLORER_MAIN_WINDOW_HPP
