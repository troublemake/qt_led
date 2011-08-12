#include <QDir>
#include <QtDebug>
#include <unistd.h>
#include <stdlib.h>
#include <map>
#include "led.h"

QString led_base_dir = "/sys/class/leds/";

static QString trigger_arr[] = {
    "none",
    "nand-disk",
    "mmc0",
    "mmc1",
    "timer",
    "heartbeat",
    "backlight",
    "gpio",
    "default-on"
};


Led::Led(Leds led):
    _gpio_number(led),
    _brightness_file(NULL),
    _brightness_stream(NULL)
{
    _led_color[LED_RED]="red";
    _led_color[LED_BLUE]="blue";
    _sys_led = new QString(QString("%1/overo:%2:gpio%3").arg(led_base_dir).arg(_led_color[led]).arg(_gpio_number));
    _sys_led_brightness = new QString(QString("%1/brightness").arg(*_sys_led));

    // set up file handles for reading/writing value
    _brightness_file = new QFile(*_sys_led_brightness);
    if (! _brightness_file->open(QIODevice::ReadWrite | QIODevice::Text)) {
            qWarning() << "Error opening brightness file for led" << _gpio_number << "\n";
    }
    _brightness_stream = new QTextStream(_brightness_file);
}

Led::~Led(){
    delete _sys_led;
}

void Led::set_state(LedState state){
    _brightness_stream->seek(0);
    if (state == LED_STATE_OFF){
        *_brightness_stream << 0;
    } else {
        *_brightness_stream << 1;
    }
}

LedState Led::get_state(){
    _brightness_stream->seek(0);
    int value;
    *_brightness_stream >> value;

    if (value == 0) {
            return LED_STATE_OFF;
    } else {
            return LED_STATE_ON;
    }
}
bool Led::set_trigger(LedTrigger trigger){
    QString sys_led_trigger = QString("%1/trigger").arg(*_sys_led);
    if (! QFile::exists(sys_led_trigger)) {
            qWarning() << "Error, GPIO direction file does not exist" << "\n";
            return false;
    }

    QFile sys_led_trigger_file(sys_led_trigger);
    if (! sys_led_trigger_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            qWarning() << "Error openning Led-Trigger direction for gpio " << _gpio_number << "\n";
            return false;
    }
    QTextStream out(&sys_led_trigger_file);

    out << trigger_arr[trigger];
}

LedTrigger Led::get_trigger(){
    QString sys_led_trigger = QString("%1/trigger").arg(*_sys_led);
            if (! QFile::exists(sys_led_trigger)) {
                    qWarning() << "Error, LED-Trigger file does not exist" << "\n";
            }

            QFile sys_led_trigger_file(sys_led_trigger);
            if (! sys_led_trigger_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    qWarning() << "Error openning Led-Trigger directory with Gpio " << _gpio_number << "\n";
                    return LED_TRIGGER_NONE;
            }

            QTextStream in(&sys_led_trigger_file);

            QString value;

            in >> value;

            for(int j=0; j < 9 ; j++)
                if(value.contains(trigger_arr[j]))
                    return (LedTrigger)j;

            return LED_TRIGGER_NONE;
}

