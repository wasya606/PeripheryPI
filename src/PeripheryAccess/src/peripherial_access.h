#ifndef __PERIPHERY_ACCESS_H__VDYKYY
#define __PERIPHERY_ACCESS_H__VDYKYY

#include "peripherial_types.h"

using namespace PeripheralTypes;

class PeripheryAccess
{
public:
    /**
     * @brief initGpio Performs initialize GPIO memory area
     * @return  PeripheryInitResult
     */
    static PeripheryInitResult initGpio();

    /**
     * @brief initI2C Performs initialize I2C memory area
     * @param device - Phisical I2C Device num
     * @return PeripheryInitResult
     */
    static PeripheryInitResult initI2C(const I2cDevice device);

    /**
     * @brief initI2C Performs initialize I2C memory area
     * @param device - Phisical I2C Device num
     * @param slaveAddress - Address of slave device (will be used as current)
     * @return PeripheryInitResult
     */
    static PeripheryInitResult initI2C(const I2cDevice device, const Reg8Addr slaveAddress);

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

    //********************************  I2C READING 8-bit address ****************************************

    static I2cAccessResult i2cReadBytes(const Reg8Addr slaveAddrr, const Reg8Addr startAddr, const Reg16Value dataLength, Byte *buffer);
    static I2cAccessResult i2cReadBytes(const Reg8Addr startAddr, const Reg16Value dataLength, Byte *buffer);

    /**
     * @brief i2cReadByte           - Performs read data from the specified register of the remote I2C slave device
     *                                If returned value is positive then the readed data will be in the first Byte
     *                                of returned int value (retValue & 0xFF).
     *                                If returned value is less than zero this means during read an error has occurred
     *                                and returned value contains the error code.
     * @param slaveAddrr            - 8-bit hardware bus address of slave device
     * @param slaveRegisterAddress  - 8-bit register address of slave device for read data
     * @return                      - readed data or I2cAccessResult::ERROR_* if error
     */
    static ReadValue i2cReadByte(const Reg8Addr slaveAddrr, const Reg8Addr slaveRegisterAddress);

    /**
     * @brief i2cReadByte           - Performs read data from the specified register of the current I2C slave device
     *                                which was stored before.
     *                                If returned value is positive then the readed data will be in the first Byte
     *                                of returned int value (retValue & 0xFF).
     *                                If returned value is less than zero this means during read an error has occurred
     *                                and returned value contains the error code.
     * @param slaveRegisterAddress  - 8-bit register address of current slave device for read data
     * @return                      - readed data or I2cAccessResult::ERROR_* if error
     */
    static ReadValue i2cReadByte(const Reg8Addr slaveRegisterAddress);

    //********************************  I2C READING 16-bit address ****************************************

    static I2cAccessResult i2cReadBytes16(const Reg8Addr slaveAddrr, const Reg16Addr startAddr, const Reg16Value dataLength, Byte *buffer);
    static I2cAccessResult i2cReadBytes16(const Reg16Addr startAddr, const Reg16Value dataLength, Byte *buffer);

    /**
     * @brief i2cReadByte           - Performs read data from the specified register of the remote I2C slave device
     *                                If returned value is positive then the readed data will be in the first Byte
     *                                of returned int value (retValue & 0xFF).
     *                                If returned value is less than zero this means during read an error has occurred
     *                                and returned value contains the error code.
     * @param slaveAddrr            - 7-bit hardware bus address of slave device
     * @param slaveRegisterAddress  - 16-bit register address of slave device for read data
     * @return                      - readed data or I2cAccessResult::ERROR_* if error
     */
    static ReadValue i2cReadByte16(const Reg8Addr slaveAddrr, const Reg16Addr slaveRegisterAddress);

    /**
     * @brief i2cReadByte           - Performs read data from the specified register of the current I2C slave device
     *                                which was stored before.
     *                                If returned value is positive then the readed data will be in the first Byte
     *                                of returned int value (retValue & 0xFF).
     *                                If returned value is less than zero this means during read an error has occurred
     *                                and returned value contains the error code.
     * @param slaveRegisterAddress  - 16-bit register address of current slave device for read data
     * @return                      - readed data or I2cAccessResult::ERROR_* if error
     */
    static ReadValue i2cReadByte16(const Reg16Addr slaveRegisterAddress);


    //*******************************  I2C WRITING 8-bit address ****************************************

    static I2cAccessResult i2cWriteBytes(const Reg8Addr slaveAddrr, const Reg8Addr startAddr,
                                         const Reg16Value dataLength, const Byte* data);
    static I2cAccessResult i2cWriteBytes(const Reg8Addr startAddr, const Reg16Value dataLength, const Byte* data);

    /**
     * @brief i2cWriteByte          - Performs write data to the specified register of the remote I2C slave device
     * @param slaveAddrr            - 8-bit hardware bus address of slave device
     * @param data                  - data to write (one Byte)
     * @param slaveRegisterAddress  - 8-bit register address of slave device for write data
     * @return                      - I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error
     */
    static I2cAccessResult i2cWriteByte(const Reg8Addr slaveAddrr, const Byte data, const Reg8Addr slaveRegisterAddress);

    /**
     * @brief i2cWriteByte          - Performs write data to the specified register of the current I2C slave device
     *                                which was setted before
     * @param data                  - data to write (one Byte)
     * @param slaveRegisterAddress  - 8-bit register address of slave device for write data
     * @return                      - I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error
     */
    static I2cAccessResult i2cWriteByte(const Byte data, const Reg8Addr slaveRegisterAddress);


    //*******************************  I2C WRITING 16-bit address ****************************************

    static I2cAccessResult i2cWriteBytes16(const Reg8Addr slaveAddrr, const Reg16Addr startAddr,
                                         const Reg16Value dataLength, const Byte* data);
    static I2cAccessResult i2cWriteBytes16(const Reg16Addr startAddr, const Reg16Value dataLength, const Byte* data);

    /**
     * @brief i2cWriteByte          - Performs write data to the specified register of the remote I2C slave device
     * @param slaveAddrr            - 8-bit hardware bus address of slave device
     * @param data                  - data to write (one Byte)
     * @param slaveRegisterAddress  - 8-bit register address of slave device for write data
     * @return                      - I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error
     */
    static I2cAccessResult i2cWriteByte16(const Reg8Addr slaveAddrr, const Byte data, const Reg16Addr slaveRegisterAddress);

    /**
     * @brief i2cWriteByte          - Performs write data to the specified register of the current I2C slave device
     *                                which was setted before
     * @param data                  - data to write (one Byte)
     * @param slaveRegisterAddress  - 8-bit register address of slave device for write data
     * @return                      - I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error
     */
    static I2cAccessResult i2cWriteByte16(const Byte data, const Reg16Addr slaveRegisterAddress);

    //*******************************  I2C OTHERS ****************************************

    /**
     * @brief setI2CCurrentSlaveAddress
     * @param slaveAddrr - I2C slave device address
     */
    static void setI2CCurrentSlaveAddress(const Reg8Addr slaveAddrr);

    /**
     * @brief getI2CCurrentSlaveAddress
     * @return I2C slave device address stored as "current"
     */
    static Reg8Addr getI2CCurrentSlaveAddress();

    /**
     * @brief setI2CFrequency Sets CLK frequency of I2C transferring
     * @param frequencyKHz - frequency in KHz (if pass 0 - frequency will be setted to 32768 Hz)
     * @return - I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error
     */
    static I2cAccessResult setI2CFrequency(const size_t frequencyKHz);

    /**
     * @brief getI2CFrequency
     * @return CLK frequency in KHz
     */
    static size_t getI2CFrequency();
};


#endif // __PERIPHERY_ACCESS_H__VDYKYY
