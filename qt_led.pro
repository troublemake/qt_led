TEMPLATE = app
TARGET = qt_led
DEPENDPATH += .
INCLUDEPATH += .

# Input
SOURCES += main.cpp \
    gpio.cpp \
    widget.cpp \
    led.cpp

HEADERS  += \
    gpio.h \
    chestnut.h \
    widget.h \
    led.h

target.path = /usr/bin
INSTALLS += target
