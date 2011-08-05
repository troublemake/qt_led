#ifndef GPIO_H
#define GPIO_H
#include <QString>
#include <QFile>
#include <QTextStream>

enum GpioDir {
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT,
    GPIO_DIR_ERROR
};

enum GpioState {
    GPIO_STATE_HIGH,
    GPIO_STATE_LOW,
    GPIO_STATE_ERROR,   // inicates an error reading GPIO state
};

class Gpio
{
private:
    bool _ready;
    GpioDir _dir;
    int _number;
    QString * _sys_gpio;
    QString * _sys_gpio_value;
    QFile * _value_file;
    QTextStream * _value_stream;

    bool _export_gpio();

public:
    // constructor
    Gpio(int gpio_number, GpioDir direction);

    // destructor
    ~Gpio();

    // initialize GPIO, return false if failed
    // this function opens up the file handle to the device
    // and verifies the direction is set correctly
    bool init();

    // get current gpio_direction
    GpioDir get_direction();

    // set gpio direction
    bool set_direction(GpioDir direction);

    // get current gpio state
    GpioState get_state();

    // set current gpio state
    bool set_state(GpioState state);
};
#endif // GPIO_H
