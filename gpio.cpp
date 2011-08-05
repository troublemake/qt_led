/*
 * Copyright 2009 Cliff Brake <cbrake@bec-systems.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <QDir>
#include <QtDebug>

#include <unistd.h>
#include <stdlib.h>

#include "gpio.h"

QString base_dir = "/sys/class/gpio";

// used to set the direction text
static QString direction_text[] = {
        "in",
        "out"
};

Gpio::Gpio(int gpio_number, GpioDir direction):
        _dir(direction),
        _number(gpio_number),
        _value_file(NULL),
        _value_stream(NULL)
{
        _ready = false;
        _sys_gpio = new QString(QString("%1/gpio%2").arg(base_dir).arg(_number));
        _sys_gpio_value = new QString(QString("%1/value").arg(*_sys_gpio));
        qDebug() << "_sys_gpio = " << *_sys_gpio << "\n";
        qDebug() << "_sys_gpio_value = " << *_sys_gpio_value << "\n";
}

Gpio::~Gpio()
{
        delete _sys_gpio;
        delete _sys_gpio_value;
        if (_value_file)
                delete _value_file;
        if (_value_stream)
                delete _value_stream;
}

// export Gpio and return false if failed
bool Gpio::_export_gpio()
{
        if (! QFile::exists(*_sys_gpio)) {
                // try to export the GPIO
                QString sys_gpio_export = QString("%1/export").arg(base_dir);
                QFile export_file(sys_gpio_export);
                if (! export_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                        qWarning() << "Error opening gpio export file for gpio" << _number << "\n";
                        return false;
                }

                QTextStream out(&export_file);
                out << _number << "\n";

                out.flush();

                // Now try again to see if the gpio has been exported
                if (! QFile::exists(*_sys_gpio)) {
                        qWarning() << "Error exporting GPIO" << _number << "\n";
                        return false;
                }

        }

        return true;
}

bool Gpio::set_direction(GpioDir direction)
{
        QString sys_gpio_direction = QString("%1/direction").arg(*_sys_gpio);
        if (! QFile::exists(sys_gpio_direction)) {
                qWarning() << "Error, GPIO direction file does not exist" << "\n";
                return false;
        }

        QFile sys_gpio_direction_file(sys_gpio_direction);
        if (! sys_gpio_direction_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                qWarning() << "Error openning gpio direction for gpio " << _number << "\n";
                return false;
        }
        QTextStream out(&sys_gpio_direction_file);
        if (direction == GPIO_DIR_INPUT) {
                out << "in" << "\n";
        } else {
                out << "out" << "\n";
        }

        _dir = direction;

        return true;
}

GpioDir Gpio::get_direction()
{
        QString sys_gpio_direction = QString("%1/direction").arg(*_sys_gpio);
        if (! QFile::exists(sys_gpio_direction)) {
                qWarning() << "Error, GPIO direction file does not exist" << "\n";
        }

        QFile sys_gpio_direction_file(sys_gpio_direction);
        if (! sys_gpio_direction_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                qWarning() << "Error openning gpio direction for gpio " << _number << "\n";
                return GPIO_DIR_ERROR;
        }

        QTextStream in(&sys_gpio_direction_file);

        QString value;

        in >> value;

        if (value.contains("out")) {
                return GPIO_DIR_OUTPUT;
        } else {
                return GPIO_DIR_INPUT;
        }
}

bool Gpio::init()
{
        // first export the GPIO if required
        if (! _export_gpio()) return false;
        if (! set_direction(_dir)) return false;

        // set up file handles for reading/writing value
        _value_file = new QFile(*_sys_gpio_value);
        if (! _value_file->open(QIODevice::ReadWrite | QIODevice::Text)) {
                qWarning() << "Error opening value file for gpio" << _number << "\n";
                return false;
        }

        _value_stream = new QTextStream(_value_file);
        _ready = true;

        return true;
}

GpioState Gpio::get_state()
{
        if (! _ready)
                return GPIO_STATE_ERROR;

        _value_stream->seek(0);
        int value;
        *_value_stream >> value;

        if (value == 0) {
                return GPIO_STATE_LOW;
        } else {
                return GPIO_STATE_HIGH;
        }
}

bool Gpio::set_state(GpioState state)
{
        if (! _ready)
                return false;

        if (_dir != GPIO_DIR_OUTPUT)
                return false;

        _value_stream->seek(0);

        if (state == GPIO_STATE_LOW) {
                *_value_stream << 0;
        } else {
                *_value_stream << 1;
        }

        return true;
}



