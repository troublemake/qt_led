#ifndef LED_H
#define LED_H
#include <map>
enum LedState {
    LED_STATE_ON,
    LED_STATE_OFF,
    LED_STATE_ERROR
};

enum Leds {
    LED_RED=21,
    LED_BLUE=22,
    LED_COM
};

enum LedTrigger {
    LED_TRIGGER_NONE,
    LED_TRIGGER_NAND_DISK,
    LED_TRIGGER_MMC0,
    LED_TRIGGER_MMC1,
    LED_TRIGGER_TIMER,
    LED_TRIGGER_HEARTBEAT,
    LED_TRIGGER_BACKLIGHT,
    LED_TRIGGER_GPIO,
    LED_TRIGGER_DEFAULT_ON
};

class Led
{
private:
    std::map<Leds, QString> _led_color;

    int _gpio_number;
    QString * _sys_led;
    QString * _sys_led_brightness;
    QFile * _brightness_file;
    QTextStream * _brightness_stream;

public:
    Led(Leds led);

    ~Led();

    void set_state(LedState state);
    LedState get_state();

    bool set_trigger(LedTrigger trigger);
    LedTrigger get_trigger();


};

#endif // LED_H
