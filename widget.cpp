#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include "widget.h"
#include "gpio.h"
#include "chestnut.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    //     setFixedSize(200, 120);

    QPushButton *ledButton = new QPushButton(tr("LED an/aus"), this);
    ledButton->setGeometry(62, 40, 140, 30);
    ledButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(ledButton, SIGNAL(clicked()),this, SLOT(on_toggle_gpio_led_red_clicked()));

    QPushButton *quitButton = new QPushButton(tr("Quit"), this);
    quitButton->setGeometry(62, 80, 75, 30);
    quitButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void Widget::on_toggle_gpio_led_blue_clicked()
{
    GpioState state = _blue_led->get_state();
    if (state == GPIO_STATE_LOW) {
        _blue_led->set_state(GPIO_STATE_HIGH);
    } else {
        _blue_led->set_state(GPIO_STATE_LOW);
    }
}

void Widget::on_toggle_gpio_led_red_clicked()
{
    GpioState state = _red_led->get_state();
    if (state == GPIO_STATE_LOW) {
        _red_led->set_state(GPIO_STATE_HIGH);
    } else {
        _red_led->set_state(GPIO_STATE_LOW);
    }
}

