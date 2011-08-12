#ifndef WIDGET_H
#define WIDGET_H
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include "gpio.h"
#include "led.h"
#include "chestnut.h"
class Widget : public QWidget {
Q_OBJECT
public:     Widget(QWidget *parent = 0);

private:
    Led * _blue_led;
    Led * _red_led;
/* The old way
    Gpio * _blue_led;
    Gpio * _red_led;
*/
private slots:
    void on_toggle_gpio_led_red_clicked();
    void on_toggle_gpio_led_blue_clicked();
};

#endif // WIDGET_H
