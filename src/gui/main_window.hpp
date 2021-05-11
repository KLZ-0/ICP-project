/**
 * @file
 * @author Adrián Kálazi (xkalaz00)
 * @author Kevin Lackó (xlacko08)
 */

#ifndef MQTT_EXPLORER_MAIN_WINDOW_HPP
#define MQTT_EXPLORER_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QPlainTextEdit>

#include "client.hpp"
#include "data_model.hpp"
#include "ui_main_window.h"

/**
 * @class MainWindow
 * @brief The main window of the application
 * Contains the explorer and dashboard tabs
 */
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
	Core::Client *client;

private slots:
	void openTopicsWindow();
	void handleTopicChange(const QSet<QString> &new_topics);
	void cancelTopicChange();
	void statusConnected();
	void statusDisconnected(const QString &reason);
	void openPublishWindow();
	void statusBarUpdate(const QString &status);
};


#endif //MQTT_EXPLORER_MAIN_WINDOW_HPP
