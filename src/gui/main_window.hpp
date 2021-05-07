/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_MAIN_WINDOW_HPP
#define MQTT_EXPLORER_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QPlainTextEdit>

#include "data_model.hpp"
#include "ui_main_window.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow() override;

private:
	Ui::MainWindow ui;
	QSet<QString> topics;
	bool topics_window_open = false;
	DataModel *dataModel;

private slots:
	void openTopicsWindow();
	void handleTopicChange(const QSet<QString> &new_topics);
	void cancelTopicChange();
};


#endif //MQTT_EXPLORER_MAIN_WINDOW_HPP
