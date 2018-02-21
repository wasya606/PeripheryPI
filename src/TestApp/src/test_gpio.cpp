#include "test_gpio.h"
#include <iostream>
#include "gpio.h"

using namespace std;

void TestGpio::writeGpio5(const bool value)
{
    cout << "\n\n\tTest write " << (value ? "\"HIGH\"" : "\"LOW\"") << " to GPIO #5\n\n";
    if (initGpio() && setGpioMode(5, OUTPUT))
    {
        GpioAccessResult accessResult = GPIO::setGpioValue(5, value);
        if (accessResult == GPIO_NO_ERRORS)
            cout << "\tGPIO #5 has been setted to " << (value ? "\"HIGH\"" : "\"LOW\"") << endl;
        else
            cout << "\tGPIO write error! Error code: " << accessResult << endl;
    }
}

void TestGpio::readGpio6()
{
    cout << "\n\n\tTest read from GPIO #6\n\n";
    if (initGpio() && setGpioMode(6, INPUT))
    {
        ReadValue value = GPIO::getGpioValue(6);
        if (value < 0)
            cout << "\tGpio read error! Error code: " << value << endl;
        else
            cout << "\tValue of GPIO #6 is: " << (value ? "\"HIGH\"" : "\"LOW\"") << endl;
    }
}

bool TestGpio::initGpio()
{
    PeripheryInitResult initResult = GPIO::initGpio();
    if (initResult != SUCCESS && initResult != ALREADY_INITIALIZED)
    {
        cout << "\tGPIO Initialization ERROR!!! Error code: " << initResult << endl;
        return false;
    }
    return true;
}

bool TestGpio::setGpioMode(const uint8_t gpioNum, const GpioMode mode)
{
    GpioAccessResult accessResult = GPIO::setGpioMode(gpioNum, mode);
    if (accessResult != GPIO_NO_ERRORS)
    {
        cout << "\tGPIO set mode error!!! Error code: " << accessResult << endl;
        return false;
    }
    return true;
}

