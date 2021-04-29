/**
 * @author Adrián Kálazi (xkalaz00)
 */

#ifndef MQTT_EXPLORER_TEST_BUTTON_H
#define MQTT_EXPLORER_TEST_BUTTON_H


#include <QPushButton>

class TestButton : public QPushButton
{
Q_OBJECT
public:
	TestButton(const QString &text, QWidget *parent);

public slots:
	void pahotest();
};


#endif //MQTT_EXPLORER_TEST_BUTTON_H
