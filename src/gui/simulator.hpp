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
	Core::Client *client = nullptr;
	QString lastSaveFile = "";
	QString fileName = "";
	bool running = false;
	bool configured = false;
	bool justLoaded = false;

public slots:
	/**
	 * @brief Loads the simulator config from an user selected file
	*/
	void load();
	/**
	 * @brief Save action
	 * Save the simulator config to a previously used savefile or ask the user for a new file
	 */
	void save();
	/**
	 * @brief Save As action
	 * Ask the user for a save file and save the dashboard to it
	*/
	void saveAs();
	/**
	 * @brief Does the actual saving
	 * Saves the dashboard to a JSON file
	 * @param filePath path to a savefile
	 */
	void saveState(const QString &filePath);

	void configureSimulator();

	void startSimulator();

	void stopSimulator();

	void configChanged();
};
