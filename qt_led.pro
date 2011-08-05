TEMPLATE = app
TARGET = qt_led
DEPENDPATH += .
INCLUDEPATH += .

# Input
SOURCES += main.cpp \
    gpio.cpp

HEADERS  += \
    gpio.h \
    chestnut.h

target.path = /usr/bin
INSTALLS += target
