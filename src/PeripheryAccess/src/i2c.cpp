#include "i2c.h"
#include <fcntl.h>
#include "hardware.h"
#include "gpio.h"
#include <stdarg.h>
#include "common.h"
#include <functional>

RegAddrPtr  I2C::i2cMappedAddress           = (RegAddrPtr)MAP_FAILED;
I2cDevice I2C::currentI2CDevice             = I2C0;
Reg8Addr I2C::currentI2CSlaveAddress        = 0x00;
I2C::I2CMapping I2C::i2cMapping             = I2C::I2CMapping();

PeripheryInitResult I2C::initI2C(const I2cDevice device)
{
    currentI2CDevice = device;
    i2cMappedAddress = i2cMapping.i2cMappedAddresses[device];
    //bool isI2cInitialized = i2cMappedAddress != nullptr;

    PeripheryInitResult result = ALREADY_INITIALIZED;
    if (!isI2cInitialized())
    {
        PeripheryInitResult gpioInitResult = ALREADY_INITIALIZED;
        if (!GPIO::isGpioInitialized())
            gpioInitResult = GPIO::initGpio();

        if (GPIO::isGpioInitialized())
        {
            I2cHardwareData i2cHardwareData = Hardware::I2C_HARDWARE_DATA(device);
            if (i2cHardwareData.BASE_ADDRESS != Hardware::WRONG_ADDRESS)
            {
                result = Common::mapPeripheryMemory(i2cHardwareData.BASE_ADDRESS, i2cMappedAddress);
                if (result == SUCCESS)
                {
                    GpioAccessResult sclSetResult =  GPIO::setGpioMode(i2cHardwareData.SCL_PIN, ALT0);
                    GpioAccessResult sdaSetResult =  GPIO::setGpioMode(i2cHardwareData.SDA_PIN, ALT0);
                    result = sclSetResult != GPIO_NO_ERRORS ? ERROR_SET_SCL_PIN : sdaSetResult != GPIO_NO_ERRORS ? ERROR_SET_SDA_PIN : SUCCESS;
                }
                i2cMapping.i2cMappedAddresses[device] = i2cMappedAddress;

            }
            else
            {
                result = ERROR_WRONG_DEVICE_NUM;
            }
        }
        else
        {
            result = gpioInitResult;
        }
    }
    return result;
}

PeripheryInitResult I2C::initI2C(const I2cDevice device, const Reg8Addr slaveAddress)
{
    PeripheryInitResult result = initI2C(device);

    if (result == SUCCESS || result == ALREADY_INITIALIZED)
    {
        currentI2CSlaveAddress = slaveAddress;
    }
    return result;
}

//********************************  I2C READING 8-bit address ****************************************
I2cAccessResult I2C::i2cReadBytes(const Reg8Addr slaveAddrr, const Reg8Addr startAddr,
                                              const Reg16Value dataLength, Byte* buffer)
{
    return i2cReadBytes(slaveAddrr, dataLength, buffer, 0x0001, startAddr);
}

I2cAccessResult I2C::i2cReadBytes(const Reg8Addr startAddr, const Reg16Value dataLength, Byte *buffer)
{
    return i2cReadBytes(currentI2CSlaveAddress, startAddr, dataLength, buffer);
}

ReadValue I2C::i2cReadByte(const Reg8Addr slaveAddrr, const Reg8Addr slaveRegisterAddress)
{
    Byte buffer = 0;
    I2cAccessResult result = i2cReadBytes(slaveAddrr, slaveRegisterAddress, 0x0001, &buffer);
    return result == I2C_NO_ERRORS ? buffer : (int)result;
}

ReadValue I2C::i2cReadByte(const Reg8Addr slaveRegisterAddress)
{
    return i2cReadByte(currentI2CSlaveAddress, slaveRegisterAddress);
}

//********************************  I2C READING 16-bit address ****************************************
I2cAccessResult I2C::i2cReadBytes16(const Reg8Addr slaveAddrr, const Reg16Addr startAddr,
                                                const Reg16Value dataLength, Byte *buffer)
{
    return i2cReadBytes(slaveAddrr, dataLength, buffer, 0x0002, (startAddr & 0xFF00) >> 8, startAddr & 0x00FF);
}

I2cAccessResult I2C::i2cReadBytes16(const Reg16Addr startAddr, const Reg16Value dataLength, Byte *buffer)
{
    return i2cReadBytes16(currentI2CSlaveAddress, startAddr, dataLength, buffer);
}

ReadValue I2C::i2cReadByte16(const Reg8Addr slaveAddrr, const Reg16Addr slaveRegisterAddress)
{
    Byte buffer = 0;
    I2cAccessResult result = i2cReadBytes16(slaveAddrr, slaveRegisterAddress, 0x0001, &buffer);
    return result == I2C_NO_ERRORS ? buffer : (int)result;
}

ReadValue I2C::i2cReadByte16(const Reg16Addr slaveRegisterAddress)
{
    return i2cReadByte16(currentI2CSlaveAddress, slaveRegisterAddress);
}

//*******************************  I2C WRITING 8-bit address ****************************************
I2cAccessResult I2C::i2cWriteBytes(const Reg8Addr slaveAddrr, const Reg8Addr startAddr,
                                               const Reg16Value dataLength, const Byte* data)
{
    return i2cWriteBytes(slaveAddrr, dataLength, data, 0x0001, startAddr);
}

I2cAccessResult I2C::i2cWriteBytes(const Reg8Addr startAddr, const Reg16Value dataLength, const Byte *data)
{
    return i2cWriteBytes(currentI2CSlaveAddress, startAddr, dataLength, data);
}

I2cAccessResult I2C::i2cWriteByte(const Reg8Addr slaveAddrr, const Byte data, const Reg8Addr slaveRegisterAddress)
{
    return i2cWriteBytes(slaveAddrr, slaveRegisterAddress, 0x0001, &data);
}


I2cAccessResult I2C::i2cWriteByte(const Byte data, const Reg8Addr slaveRegisterAddress)
{
    return i2cWriteByte(currentI2CSlaveAddress, data, slaveRegisterAddress);
}

//*******************************  I2C WRITING 16-bit address ****************************************
I2cAccessResult I2C::i2cWriteBytes16(const Reg8Addr slaveAddrr, const Reg16Addr startAddr,
                                                 const Reg16Value dataLength, const Byte *data)
{
    return i2cWriteBytes(slaveAddrr, dataLength, data, 0x0002, (startAddr & 0xFF00) >> 8, startAddr & 0x00FF);
}

I2cAccessResult I2C::i2cWriteBytes16(const Reg16Addr startAddr, const Reg16Value dataLength, const Byte *data)
{
    return i2cWriteBytes16(currentI2CSlaveAddress, startAddr, dataLength, data);
}

I2cAccessResult I2C::i2cWriteByte16(const Reg8Addr slaveAddrr, const Byte data, const Reg16Addr slaveRegisterAddress)
{
    return i2cWriteBytes16(slaveAddrr, slaveRegisterAddress, 0x0001, &data);
}

I2cAccessResult I2C::i2cWriteByte16(const Byte data, const Reg16Addr slaveRegisterAddress)
{
    return i2cWriteByte16(currentI2CSlaveAddress, data, slaveRegisterAddress);
}

//*******************************  I2C OTHERS ****************************************
void I2C::setI2CCurrentSlaveAddress(const Reg8Addr slaveAddrr)
{
    currentI2CSlaveAddress = slaveAddrr;
}

Reg8Addr I2C::getI2CCurrentSlaveAddress()
{
    return currentI2CSlaveAddress;
}

I2cAccessResult I2C::setI2CFrequency(const size_t frequencyKHz)
{
    *I2C_CLK_DIV_REG() = (frequencyKHz / 100) & Hardware::I2C_DIV_CDIV_MASK;
    return I2C_NO_ERRORS;
}

size_t I2C::getI2CFrequency()
{
    return (*I2C_CLK_DIV_REG() & Hardware::I2C_DIV_CDIV_MASK) * 100;
}

I2cAccessResult I2C::i2cReadBytes(const Reg8Addr slaveAddrr, const Reg16Value dataLength, Byte *dataBuffer,
                                              const Reg16Value addrLength, const Reg8Addr startAddrFirstByte, ...)
{
    I2cAccessResult result = ERROR_I2C_NOT_INITIALIZED;

    i2cMappedAddress = i2cMapping.i2cMappedAddresses[currentI2CDevice];

    if (isI2cInitialized())
    {
        //Set slave address
        *I2C_SLAVE_ADDR_REG() = slaveAddrr & Hardware::I2C_A_ADDR_MASK;

        //------- Write slave register start address ----//
        //Set address length
        *I2C_DATA_LEN_REG() = addrLength & Hardware::I2C_DLEN_DLEN_MASK;

        va_list vaList;
        va_start(vaList, startAddrFirstByte);

        //Set address bytes
        *I2C_FIFO_REG() = startAddrFirstByte & Hardware::I2C_FIFO_DATA_MASK;
        for (Reg16Addr i = 1; i < addrLength; i++)
            *I2C_FIFO_REG() = va_arg(vaList, int) & Hardware::I2C_FIFO_DATA_MASK;

        //Write slave register address
        startI2CWrite();

        result = waitForI2COperationDone();

        //------------- Read data --------------//
        if (result == I2C_NO_ERRORS)
        {
            //Set data length
            *I2C_DATA_LEN_REG() = dataLength & Hardware::I2C_DLEN_DLEN_MASK;

            //Read data recursive lambda
            std::function<I2cAccessResult(Reg16Addr, size_t)> readDataFromFIFO = [&readDataFromFIFO, dataBuffer]
                                                               (Reg16Addr i, size_t sleeps) -> I2cAccessResult
            {
                if (*I2C_STATUS_REG() & Hardware::I2C_S_RXD_MASK)
                {
                    dataBuffer[i] = *I2C_FIFO_REG() & Hardware::I2C_FIFO_DATA_MASK;
                    return readDataFromFIFO(i + 1, 0);
                }
                else
                {
                    if ((*I2C_STATUS_REG() & Hardware::I2C_S_DONE_MASK))
                    {
                        return I2C_NO_ERRORS;
                    }
                    else if (*I2C_STATUS_REG() & Hardware::I2C_S_ERR_MASK)
                    {
                        return ERROR_I2C_SLAVE_ADDRESS;
                    }
                    else if (*I2C_STATUS_REG() & Hardware::I2C_S_CLKT_MASK)
                    {
                        return ERROR_I2C_OPERATION_CLKT;
                    }
                    else if (sleeps < I2C_TIMEOUT)
                    {
                        usleep(5);
                        return readDataFromFIFO(i, sleeps + 5);
                    }
                    else
                    {
                        return ERROR_I2C_OPERATION_TIMEOUT;
                    }
                }
            };

            //Read
            startI2CRead();
            result = readDataFromFIFO(0, 0);
        }
        clearI2CStatusReg();
    }
    return result;
}

I2cAccessResult I2C::i2cWriteBytes(const Reg8Addr slaveAddrr, const Reg16Value dataLength, const Byte *data,
                                               const Reg16Value addrLength, const Reg8Addr startAddrFirstByte, ...)
{
    i2cMappedAddress = i2cMapping.i2cMappedAddresses[currentI2CDevice];

    I2cAccessResult result = ERROR_I2C_NOT_INITIALIZED;
    if (isI2cInitialized())
    {
        //Set slave address
        *I2C_SLAVE_ADDR_REG() = slaveAddrr & Hardware::I2C_A_ADDR_MASK;

        //Set data length
        *I2C_DATA_LEN_REG() = (addrLength + dataLength) & Hardware::I2C_DLEN_DLEN_MASK;

        va_list vaList;
        va_start(vaList, startAddrFirstByte);

        //Set slave register start address
        *I2C_FIFO_REG() = startAddrFirstByte & Hardware::I2C_FIFO_DATA_MASK;
        for (Reg16Addr i = 1; i < addrLength; i++)
            *I2C_FIFO_REG() = va_arg(vaList, int) & Hardware::I2C_FIFO_DATA_MASK;

        std::function<void(const Byte)> pushByteToFIFO = [&pushByteToFIFO](const Byte data) -> void
        {
            if ((!(*I2C_STATUS_REG() & Hardware::I2C_S_TA_MASK) && (*I2C_STATUS_REG() & Hardware::I2C_S_TXD_MASK)) ||
                 ((*I2C_STATUS_REG() & Hardware::I2C_S_TA_MASK) && (*I2C_STATUS_REG() & Hardware::I2C_S_TXW_MASK)))
            {
                *I2C_FIFO_REG() = data & Hardware::I2C_FIFO_DATA_MASK;
            }
            else
            {
                if (!(*I2C_STATUS_REG() & Hardware::I2C_S_TA_MASK))
                    startI2CWrite();
                usleep(5);
                pushByteToFIFO(data);
            }
        };

        //Set write data
        for (Byte i = 0; i < dataLength; i++)
        {
            pushByteToFIFO(data[i]);
        }

        if (!(*I2C_STATUS_REG() & Hardware::I2C_S_TA_MASK))
            startI2CWrite();

        result = waitForI2COperationDone();
        clearI2CStatusReg();
    }
    return result;
}

constexpr RegAddrPtr I2C::I2C_CONTROL_REG(RegAddrPtr  mAddr)     { return mAddr + Hardware::I2C_C_REG_OFFSET;    }
constexpr RegAddrPtr I2C::I2C_STATUS_REG(RegAddrPtr mAddr)       { return mAddr + Hardware::I2C_S_REG_OFFSET;    }
constexpr RegAddrPtr I2C::I2C_DATA_LEN_REG(RegAddrPtr  mAddr)    { return mAddr + Hardware::I2C_DLEN_REG_OFFSET; }
constexpr RegAddrPtr I2C::I2C_SLAVE_ADDR_REG(RegAddrPtr mAddr)   { return mAddr + Hardware::I2C_A_REG_OFFSET;    }
constexpr RegAddrPtr I2C::I2C_FIFO_REG(RegAddrPtr  mAddr)        { return mAddr + Hardware::I2C_FIFO_REG_OFFSET; }
constexpr RegAddrPtr I2C::I2C_CLK_DIV_REG(RegAddrPtr mAddr)      { return mAddr + Hardware::I2C_DIV_REG_OFFSET;  }
constexpr RegAddrPtr I2C::I2C_DATA_DELAY_REG(RegAddrPtr  mAddr)  { return mAddr + Hardware::I2C_DEL_REG_OFFSET;  }
constexpr RegAddrPtr I2C::I2C_CLKT_REG(RegAddrPtr mAddr)         { return mAddr + Hardware::I2C_CLKT_REG_OFFSET; }


inline bool I2C::isI2cInitialized()
{
    return i2cMappedAddress != (RegAddrPtr)MAP_FAILED && i2cMappedAddress != nullptr;
}

I2cAccessResult I2C::waitForI2COperationDone(const size_t msTimeout)
{
    bool isDone = false;
    for (size_t i = 0; i <= msTimeout && !isDone; i++)
    {
        usleep(1000);
        isDone = *I2C_STATUS_REG() & Hardware::I2C_S_DONE_MASK;
    }

    bool isError = *I2C_STATUS_REG() & Hardware::I2C_S_ERR_MASK;
    bool isClktError = *I2C_STATUS_REG() & Hardware::I2C_S_CLKT_MASK;

    return (isDone && !isError && !isClktError) ? I2C_NO_ERRORS             :
           (isError)                            ? ERROR_I2C_SLAVE_ADDRESS   :
           (isClktError)                        ?  ERROR_I2C_OPERATION_CLKT :
           ERROR_I2C_OPERATION_TIMEOUT;
}

void I2C::clearI2CStatusReg()
{
    *I2C_STATUS_REG() = Hardware::I2C_S_CLKT_MASK | Hardware::I2C_S_ERR_MASK | Hardware::I2C_S_DONE_MASK;
}

void I2C::startI2CRead()
{
    clearI2CStatusReg();
    *I2C_CONTROL_REG() = Hardware::I2C_C_I2CEN_MASK | Hardware::I2C_C_ST_MASK |
                         Hardware::I2C_C_CLEAR_MASK | Hardware::I2C_C_READ_MASK;
}

void I2C::startI2CWrite()
{
    clearI2CStatusReg();
    *I2C_CONTROL_REG() = Hardware::I2C_C_I2CEN_MASK | Hardware::I2C_C_ST_MASK;
}
