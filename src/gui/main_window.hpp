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
	QVector<QString> topics;
	bool topics_window_open = false;

private slots:
	void openTopicsWindow();
	void handleTopicChange(const QVector<QString> &new_topics);
};


#endif //MQTT_EXPLORER_MAIN_WINDOW_HPP
