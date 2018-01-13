TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /mnt/RPI3/rootfs/usr/include/
INCLUDEPATH += /mnt/RPI3/rootfs/usr/include/c++/4.9
INCLUDEPATH += /mnt/RPI3/rootfs/usr/include/arm-linux-gnueabihf

HEADERS += \

SOURCES += src/main.cpp \

include(src/TestApp/TestApp.pri)
include(src/PeripheryAccess/PeripheryAccess.pri)
include(src/Drivers/Drivers.pri)

LIBS += -lpthread

TARGET = TestPeriphery

INSTALLS        = target
target.path     = /home/pi/PeripheryTest

