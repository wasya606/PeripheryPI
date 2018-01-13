#ifndef GPIO_H___VDYKYY___
#define GPIO_H___VDYKYY___
#include <cstddef>
#include "peripherial_types.h"


using namespace PeripheralTypes;
class GPIO
{
public:
    /**
     * @brief initGpio Performs initialize GPIO memory area
     * @return  PeripheryInitResult
     */
    static PeripheryInitResult initGpio();
    /**
     * @brief setGpioMode
     * @param gpioNum
     * @param mode
     * @return GpioAccessResult::GPIO_NO_ERRORS if success or GpioAccessResult::ERROR_* if error
     */
    static GpioAccessResult setGpioMode(const Byte gpioNum, const GpioMode mode);

    /**
     * @brief getGpioMode
     * @param gpioNum
     * @return Hardware::GpioMode or GpioAccessResult::ERROR_* if error
     */
    static ReadValue getGpioMode(const Byte gpioNum);

    /**
     * @brief setGpioValue
     * @param gpioNum
     * @param value
     * @return GpioAccessResult::GPIO_NO_ERRORS if success or GpioAccessResult::ERROR_* if error
     */
    static GpioAccessResult setGpioValue(const Byte gpioNum, const bool value);

    /**
     * @brief getGpioValue
     * @param gpioNum
     * @return GpioValue or GpioAccessResult::ERROR_* if error
     */
    static ReadValue getGpioValue(const Byte gpioNum);

    static bool isGpioInitialized();

private:
    static inline GpioAccessResult checkGpioAccessError(const Byte gpioNum);
private:
    static RegAddrPtr  gpioMappedAddress;
};

#endif // GPIO_H___VDYKYY___
