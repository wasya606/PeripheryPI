#ifndef __HARDWARE_HPP_RPI3__VDYKYY__LUXOFT__
#define __HARDWARE_HPP_RPI3__VDYKYY__LUXOFT__
#include "hardware.h"
#include <cstddef>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>

constexpr RegAddrPtr Hardware::GPIO_MODE_REG_ADDRESS(const Byte gpioNum, BaseAddrPtr mappedGpioAddress)
{
    return mappedGpioAddress + GPIO_MODE_REGS_OFFSET + gpioNum / GPIO_MODE_VALUES_PER_REG;
}

constexpr RegAddrPtr Hardware::GPIO_SET_HIGH_VALUE_REG_ADDRESS(const Byte gpioNum, BaseAddrPtr mappedGpioAddress)
{
    return mappedGpioAddress + GPIO_SET_HIGH_VALUE_OFFSET + gpioNum / GPIO_LEVEL_VALUES_PER_REG;
}

constexpr RegAddrPtr Hardware::GPIO_SET_LOW_VALUE_REG_ADDRESS(const Byte gpioNum, BaseAddrPtr mappedGpioAddress)
{
    return mappedGpioAddress + GPIO_SET_LOW_VALUE_OFFSET + gpioNum / GPIO_LEVEL_VALUES_PER_REG;
}

constexpr RegAddrPtr Hardware::GPIO_GET_VALUE_REG_ADDRESS(const Byte gpioNum, BaseAddrPtr mappedGpioAddress)
{
    return mappedGpioAddress + GPIO_GET_CURRENT_VALUE_OFFSET + gpioNum / GPIO_LEVEL_VALUES_PER_REG;
}

constexpr BaseBitMask Hardware::GPIO_MODE_BIT0_MASK(const Byte gpioNum)
{
    return (gpioNum % (GPIO_REGISTERS_WIDTH / GPIO_MODE_VALUE_BITS)) * GPIO_MODE_VALUE_BITS;
}

constexpr BaseBitMask Hardware::GPIO_MODE_BITS_MASK(const Byte gpioNum)
{
    return (1 << GPIO_MODE_BIT0_MASK(gpioNum)) | (1 << GPIO_MODE_BIT0_MASK(gpioNum) << 1) | (1 << GPIO_MODE_BIT0_MASK(gpioNum) << 2);
}

constexpr BaseBitMask Hardware::GPIO_VALUE_BIT_MASK(const Byte gpioNum)
{
    return (1 << ((gpioNum % (GPIO_REGISTERS_WIDTH / GPIO_LEVEL_VALUE_BITS)) * GPIO_LEVEL_VALUE_BITS));
}

constexpr I2cHardwareData Hardware::I2C_HARDWARE_DATA(const Byte i2cDevice)
{
    return i2cDevice == 0 ? I2cHardwareData(I2C0_BASE_ADDRESS, 0, 1)   :
           i2cDevice == 1 ? I2cHardwareData(I2C1_BASE_ADDRESS, 2, 3)   :
           i2cDevice == 2 ? I2cHardwareData(I2C2_BASE_ADDRESS, 44, 45) :
           I2cHardwareData(WRONG_ADDRESS, WRONG_PIN, WRONG_PIN);
}

constexpr SpiHardwareData Hardware::SPI_HARDWARE_DATA()
{
    return SpiHardwareData(SPI0_BASE_ADDRESS, 9, 10, 11, 8, 7, WRONG_PIN, ALT0);
}

#endif //__HARDWARE_HPP_RPI3__VDYKYY__LUXOFT__
