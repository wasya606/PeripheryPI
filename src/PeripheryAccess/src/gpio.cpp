#include "gpio.h"
#include "hardware.h"
#include "common.h"
#include <sys/mman.h>

RegAddrPtr  GPIO::gpioMappedAddress = (RegAddrPtr)MAP_FAILED;

PeripheryInitResult GPIO::initGpio()
{
    PeripheryInitResult result = ALREADY_INITIALIZED;
    if (!isGpioInitialized())
        result = Common::mapPeripheryMemory(Hardware::GPIO_BASE_ADDRESS, gpioMappedAddress);

    return result;
}

ReadValue GPIO::getGpioMode(const Byte gpioNum)
{
    const GpioAccessResult accessError = checkGpioAccessError(gpioNum);
    if (accessError == GPIO_NO_ERRORS)
    {
        return (*Hardware::GPIO_MODE_REG_ADDRESS(gpioNum, gpioMappedAddress)
                & Hardware::GPIO_MODE_BITS_MASK(gpioNum)) >> Hardware::GPIO_MODE_BIT0_MASK(gpioNum);
    }
    return accessError;
}

GpioAccessResult GPIO::setGpioMode(const Byte gpioNum, const GpioMode mode)
{
    const GpioAccessResult accessError = checkGpioAccessError(gpioNum);
    if (accessError == GPIO_NO_ERRORS)
    {
        *Hardware::GPIO_MODE_REG_ADDRESS(gpioNum, gpioMappedAddress) = (*Hardware::GPIO_MODE_REG_ADDRESS(gpioNum, gpioMappedAddress) &
                                                              (~Hardware::GPIO_MODE_BITS_MASK(gpioNum))) ^
                (mode << Hardware::GPIO_MODE_BIT0_MASK(gpioNum));
    }
    return accessError;
}

GpioAccessResult GPIO::setGpioValue(const Byte gpioNum, const bool value)
{
    const GpioAccessResult accessError = checkGpioAccessError(gpioNum);
    if (accessError == GPIO_NO_ERRORS)
    {
        RegAddrPtr gpioValuesPtr = value == HIGH ? Hardware::GPIO_SET_HIGH_VALUE_REG_ADDRESS(gpioNum, gpioMappedAddress) :
                                                  Hardware::GPIO_SET_LOW_VALUE_REG_ADDRESS(gpioNum, gpioMappedAddress);
        *gpioValuesPtr = Hardware::GPIO_VALUE_BIT_MASK(gpioNum);
    }
    return accessError;
}

ReadValue GPIO::getGpioValue(const Byte gpioNum)
{
    const GpioAccessResult accessError = checkGpioAccessError(gpioNum);
    if (accessError == GPIO_NO_ERRORS)
    {
        return ((*Hardware::GPIO_GET_VALUE_REG_ADDRESS(gpioNum, gpioMappedAddress)) &
                (Hardware::GPIO_VALUE_BIT_MASK(gpioNum))) == 0 ? LOW : HIGH;
    }
    return accessError;
}

inline bool GPIO::isGpioInitialized()
{
    return gpioMappedAddress != (RegAddrPtr)MAP_FAILED && gpioMappedAddress != nullptr;
}

GpioAccessResult GPIO::checkGpioAccessError(const Byte gpioNum)
{
    return (!isGpioInitialized()) ? ERROR_GPIO_NOT_INITIALIZED : (gpioNum >= Hardware::GPIO_COUNT) ? ERROR_WRONG_GPIO_NUM : GPIO_NO_ERRORS;
}
