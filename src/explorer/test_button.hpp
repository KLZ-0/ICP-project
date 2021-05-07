/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_TEST_BUTTON_H
#define MQTT_EXPLORER_TEST_BUTTON_H


#include <QPushButton>

#include "core/client.hpp"

class TestButton : public QPushButton
{
	Q_OBJECT
public:
	TestButton(const QString &text, QWidget *parent, Core::Client *client);

public slots:
	void pahotest();

private:
	Core::Client *client_;
};


#endif //MQTT_EXPLORER_TEST_BUTTON_H
