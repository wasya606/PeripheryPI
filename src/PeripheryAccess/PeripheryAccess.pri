INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/hardware

HEADERS += \
    $$PWD/src/peripherial_access.h \
    $$PWD/src/peripherial_types.h \
    $$PWD/src/hardware/hardware.h \
    $$PWD/src/hardware/hardware.hpp \
    $$PWD/src/taskmanager.h \
    $$PWD/src/gpio.h \
    $$PWD/src/i2c.h \
    $$PWD/src/spi.h \
    $$PWD/src/common.h \
    $$PWD/src/spisettings.h

SOURCES += \
    $$PWD/src/peripherial_access.cpp \
    $$PWD/src/taskmanager.cpp \
    $$PWD/src/gpio.cpp \
    $$PWD/src/i2c.cpp \
    $$PWD/src/spi.cpp \
    $$PWD/src/common.cpp \
    $$PWD/src/spisettings.cpp

