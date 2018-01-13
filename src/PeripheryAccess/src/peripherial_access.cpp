#include "peripherial_access.h"
#include "gpio.h"
#include "i2c.h"

PeripheryInitResult PeripheryAccess::initGpio()
{
    return GPIO::initGpio();
}

PeripheryInitResult PeripheryAccess::initI2C(const I2cDevice device)
{
    return I2C::initI2C(device);
}

PeripheryInitResult PeripheryAccess::initI2C(const I2cDevice device, const Reg8Addr slaveAddress)
{
    return I2C::initI2C(device, slaveAddress);
}

ReadValue PeripheryAccess::getGpioMode(const Byte gpioNum)
{
    return GPIO::getGpioMode(gpioNum);
}

GpioAccessResult PeripheryAccess::setGpioMode(const Byte gpioNum, const GpioMode mode)
{
    return GPIO::setGpioMode(gpioNum, mode);
}

GpioAccessResult PeripheryAccess::setGpioValue(const Byte gpioNum, const bool value)
{
    return GPIO::setGpioValue(gpioNum, value);
}

ReadValue PeripheryAccess::getGpioValue(const Byte gpioNum)
{
    return GPIO::getGpioValue(gpioNum);
}

//********************************  I2C READING 8-bit address ****************************************
I2cAccessResult PeripheryAccess::i2cReadBytes(const Reg8Addr slaveAddrr, const Reg8Addr startAddr,
                                              const Reg16Value dataLength, Byte* buffer)
{
    return I2C::i2cReadBytes(slaveAddrr, startAddr, dataLength, buffer);
}

I2cAccessResult PeripheryAccess::i2cReadBytes(const Reg8Addr startAddr, const Reg16Value dataLength, Byte *buffer)
{
    return I2C::i2cReadBytes(startAddr, dataLength, buffer);
}

ReadValue PeripheryAccess::i2cReadByte(const Reg8Addr slaveAddrr, const Reg8Addr slaveRegisterAddress)
{
    return I2C::i2cReadByte(slaveAddrr, slaveRegisterAddress);
}

ReadValue PeripheryAccess::i2cReadByte(const Reg8Addr slaveRegisterAddress)
{
    return I2C::i2cReadByte(slaveRegisterAddress);
}

//********************************  I2C READING 16-bit address ****************************************
I2cAccessResult PeripheryAccess::i2cReadBytes16(const Reg8Addr slaveAddrr, const Reg16Addr startAddr,
                                                const Reg16Value dataLength, Byte *buffer)
{
    return I2C::i2cReadBytes16(slaveAddrr, startAddr, dataLength, buffer);
}

I2cAccessResult PeripheryAccess::i2cReadBytes16(const Reg16Addr startAddr, const Reg16Value dataLength, Byte *buffer)
{
    return I2C::i2cReadBytes16(startAddr, dataLength, buffer);
}

ReadValue PeripheryAccess::i2cReadByte16(const Reg8Addr slaveAddrr, const Reg16Addr slaveRegisterAddress)
{
    return I2C::i2cReadByte16(slaveAddrr, slaveRegisterAddress);
}

ReadValue PeripheryAccess::i2cReadByte16(const Reg16Addr slaveRegisterAddress)
{
    return I2C::i2cReadByte16(slaveRegisterAddress);
}

//*******************************  I2C WRITING 8-bit address ****************************************
I2cAccessResult PeripheryAccess::i2cWriteBytes(const Reg8Addr slaveAddrr, const Reg8Addr startAddr,
                                               const Reg16Value dataLength, const Byte* data)
{
    return I2C::i2cWriteBytes(slaveAddrr, startAddr, dataLength, data);
}

I2cAccessResult PeripheryAccess::i2cWriteBytes(const Reg8Addr startAddr, const Reg16Value dataLength, const Byte *data)
{
    return I2C::i2cWriteBytes(startAddr, dataLength, data);
}

I2cAccessResult PeripheryAccess::i2cWriteByte(const Reg8Addr slaveAddrr, const Byte data, const Reg8Addr slaveRegisterAddress)
{
    return I2C::i2cWriteByte(slaveAddrr, data, slaveRegisterAddress);
}


I2cAccessResult PeripheryAccess::i2cWriteByte(const Byte data, const Reg8Addr slaveRegisterAddress)
{
    return I2C::i2cWriteByte(data, slaveRegisterAddress);
}

//*******************************  I2C WRITING 16-bit address ****************************************
I2cAccessResult PeripheryAccess::i2cWriteBytes16(const Reg8Addr slaveAddrr, const Reg16Addr startAddr,
                                                 const Reg16Value dataLength, const Byte *data)
{
    return I2C::i2cWriteBytes16(slaveAddrr, startAddr, dataLength, data);
}

I2cAccessResult PeripheryAccess::i2cWriteBytes16(const Reg16Addr startAddr, const Reg16Value dataLength, const Byte *data)
{
    return I2C::i2cWriteBytes16(startAddr, dataLength, data);
}

I2cAccessResult PeripheryAccess::i2cWriteByte16(const Reg8Addr slaveAddrr, const Byte data, const Reg16Addr slaveRegisterAddress)
{
    return I2C::i2cWriteByte16(slaveAddrr, data, slaveRegisterAddress);
}

I2cAccessResult PeripheryAccess::i2cWriteByte16(const Byte data, const Reg16Addr slaveRegisterAddress)
{
    return I2C::i2cWriteByte16(data, slaveRegisterAddress);
}

//*******************************  I2C OTHERS ****************************************
void PeripheryAccess::setI2CCurrentSlaveAddress(const Reg8Addr slaveAddrr)
{
    I2C::setI2CCurrentSlaveAddress(slaveAddrr);
}

Reg8Addr PeripheryAccess::getI2CCurrentSlaveAddress()
{
    return I2C::getI2CCurrentSlaveAddress();
}

I2cAccessResult PeripheryAccess::setI2CFrequency(const size_t frequencyKHz)
{
    return I2C::setI2CFrequency(frequencyKHz);
}

size_t PeripheryAccess::getI2CFrequency()
{
    return I2C::getI2CFrequency();
}

