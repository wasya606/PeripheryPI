#ifndef TEST_GPIO_H
#define TEST_GPIO_H
#include "peripherial_types.h"

using namespace PeripheralTypes;

class TestGpio
{
public:
    TestGpio() = delete;
    static void writeGpio5(const bool value);
    static void readGpio6();

private:
    static bool initGpio();
    static bool setGpioMode(const uint8_t gpioNum, const GpioMode mode);

};

#endif // TEST_GPIO_H
