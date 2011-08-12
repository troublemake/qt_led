#include <QApplication>
#include <QtDebug>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include "widget.h"
#include "gpio.h"
#include "led.h"
#include "chestnut.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent) {
    //     setFixedSize(200, 120);
/* The old way over GPIO:
     _blue_led = new Gpio(OVERO_GPIO_CHESTNUT_BLUE_LED, GPIO_DIR_OUTPUT);
*/
    _blue_led = new Led(LED_BLUE);

    QPushButton *ledButton = new QPushButton(tr("LED an/aus"), this);
    ledButton->setGeometry(62, 40, 140, 30);
    ledButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(ledButton, SIGNAL(clicked()),this, SLOT(on_toggle_gpio_led_blue_clicked()));

    QPushButton *quitButton = new QPushButton(tr("Quit"), this);
    quitButton->setGeometry(62, 80, 75, 30);
    quitButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
/* The old way initialize GPIO Port
    if (! _blue_led->init())
    {
            qWarning() << "Error initializing GPIO" << "\n";
    }
 */
}

void Widget::on_toggle_gpio_led_blue_clicked()
{
    LedState state = _blue_led->get_state();
    if (state == LED_STATE_OFF)
        _blue_led->set_state(LED_STATE_ON);
    else
        _blue_led->set_state(LED_STATE_OFF);
 /* The old way
    GpioState state = _blue_led->get_state();
    if (state == GPIO_STATE_LOW) {
        _blue_led->set_state(GPIO_STATE_HIGH);
    } else {
        _blue_led->set_state(GPIO_STATE_LOW);
    }
   */
}

void Widget::on_toggle_gpio_led_red_clicked()
{
    LedState state = _red_led->get_state();
    if (state == LED_STATE_OFF)
        _red_led->set_state(LED_STATE_ON);
    else
        _red_led->set_state(LED_STATE_OFF);
 /* The old way
    GpioState state = _red_led->get_state();
    if (state == GPIO_STATE_LOW) {
        _red_led->set_state(GPIO_STATE_HIGH);
    } else {
        _red_led->set_state(GPIO_STATE_LOW);
    }
  */
}

