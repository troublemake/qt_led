TEMPLATE = app
TARGET = qt_led
DEPENDPATH += .
INCLUDEPATH += .

# Input
SOURCES += main.cpp \
    gpio.cpp \
    widget.cpp

HEADERS  += \
    gpio.h \
    chestnut.h \
    widget.h

target.path = /usr/bin
INSTALLS += target
