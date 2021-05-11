/**
 * @file
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_TOPIC_SELECTION_WINDOW_HPP
#define MQTT_EXPLORER_TOPIC_SELECTION_WINDOW_HPP

#include <QWidget>

#include "ui_topic_selection_window.h"

/**
 * @class TopicSelectionWindow
 * @brief Represents a window for topic selection
 * Creates a window for managing topics
 * From the user perspective the window requires a list of initial topics and returns a list of selected topics
 * @note Differentiation of subscribe/unsubscribe topics should be handled separately
 * This window has it's own lifecycle
 */
class TopicSelectionWindow : public QWidget
{
	Q_OBJECT

public:
	explicit TopicSelectionWindow(const QSet<QString> &topics);

private:
	Ui::TopicSelectionWindow ui;

signals:
	void topicsSelected(const QSet<QString> &topics);

private slots:
	void addNewTopic(QString topic = nullptr);
	void removeSelectedTopic();
	void checkForDuplicates(QTreeWidgetItem *item, int column);
	void confirmChanges();
};


#endif //MQTT_EXPLORER_TOPIC_SELECTION_WINDOW_HPP
