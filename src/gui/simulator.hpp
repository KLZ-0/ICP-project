/**
 * @author Kevin Lackó (xlacko08)
 */
#pragma once


#include <QJsonDocument>
#include <QWidget>
#include "client.hpp"

#include "ui_simulator.h"

/**
 * @class Simulator
 * @brief Represents the simulator tab
 * The UI contains a text editor for the configuration json
 * and buttons for controlling the simulation
 */
class Simulator : public QWidget
{
	Q_OBJECT

public:
	Simulator();

private:
	Ui::Simulator ui;
	Core::Client *client;
	QString lastSaveFile = "";

public slots:
	void save();
	void saveAs();
	void saveState(const QString &filePath);
};
