#ifndef __PERIPHERIAL_TYPES__VDYKYY
#define __PERIPHERIAL_TYPES__VDYKYY
#include <cstdint>
#include <cstddef>
#include <functional>

namespace PeripheralTypes
{
    using BaseAddr              = uint32_t;
    using BaseAddrPtr           = volatile uint32_t*;
    using RegAddrPtr            = volatile uint32_t*;

    using ReadValue             = int;

    using RegOffset             = uint8_t;
    using Reg8Addr              = uint8_t;
    using Reg16Addr             = uint16_t;
    using Reg8Value             = uint8_t;
    using Reg16Value            = uint16_t;
    using Reg32Value            = uint32_t;
    using Byte                  = uint8_t;

    using BaseOffset            = BaseAddr;
    using BaseBitMask           = BaseAddr;
    using Reg8BitMask           = Reg8Value;
    using Reg8AddrMask          = Reg8Addr;

    using TaskId                = uint32_t;
    using TaskParameters        = void*;

    using TaskDelegate          = std::function<void(const TaskId, const TaskParameters)>;
    using SpiTransferCallback   = std::function<void(const TaskId, const uint32_t*, const Byte)>;

    //template<typename T>
    //using SpiTransferCallback2   = void (T::*)(const TaskId, const uint32_t*, const Byte);


    //----------------------------------------------------------------------------------------

    //Avaliable GPIO modes (INPUT, OUTPUT, ADC, I2C, SPI, PWM, ...)
    //Allows to set a one of bellow function separately for each GPIO pin
    //For detail see tables in "../Docs/DataSheets/BCM2835-ARM-Peripherals.pdf" pages 102-104
    enum GpioMode
    {
        INPUT   = 0b000,    //Digital input (Allows read logic level from pin)
        OUTPUT  = 0b001,    //Digital output (Allows set a logic level on pin)
        ALT0    = 0b100,    //Alternate function 0
        ALT1    = 0b101,    //Alternate function 1
        ALT2    = 0b110,    //Alternate function 2
        ALT3    = 0b111,    //Alternate function 3
        ALT4    = 0b011,    //Alternate function 4
        ALT5    = 0b010     //Alternate function 5
    };

    enum PeripheryInitResult
    {
        SUCCESS = 0xFF,
        ALREADY_INITIALIZED = 0x0F,
        ERROR_OPEN_MEM_DEV = -1,
        ERROR_MEM_MAP = -2,
        ERROR_WRONG_DEVICE_NUM = -3,
        ERROR_SET_SCL_PIN = -4,
        ERROR_SET_SDA_PIN = -5,
        ERROR_SET_SPI_PIN = -6
    };

    enum GpioAccessResult
    {
        GPIO_NO_ERRORS = 0xFF,
        ERROR_WRONG_GPIO_NUM = -1,
        ERROR_GPIO_NOT_INITIALIZED = -2,
        OTHER_GPIO_ACCESS_ERROR = -3
    };

    enum I2cAccessResult
    {
        I2C_NO_ERRORS = 0xFF,
        ERROR_WRITE_I2C_REG = -1,
        ERROR_READ_I2C_REG = -2,
        ERROR_I2C_NOT_INITIALIZED = -3,
        ERROR_I2C_OPERATION_TIMEOUT = -4,
        ERROR_I2C_OPERATION_CLKT = -5,
        ERROR_I2C_SLAVE_ADDRESS = -6
    };

    enum SpiAccessResult
    {
        SPI_NO_ERRORS = 0xFF,
        ERROR_SPI_NOT_INITIALIZED = -1,
        OTHER_SPI_ACCESS_ERROR = -2
    };

    enum GpioValue
    {
        LOW = 0,
        HIGH = 1
    };

    enum I2cDevice
    {
        I2C0 = 0,
        I2C1 = 1,
        I2C2 = 2
    };

    namespace SpiDevice {
    enum Device
    {
        SPI0 = 0,
        SPI1 = 1
    };
    }

    //----------------------------------------------------------------------------------------

    struct I2cHardwareData
    {
        constexpr I2cHardwareData(const BaseAddr baseAddress, const Byte sda, const Byte scl) :
                                BASE_ADDRESS(baseAddress), SDA_PIN(sda), SCL_PIN(scl) {}

        BaseAddr BASE_ADDRESS;
        Byte SDA_PIN;
        Byte SCL_PIN;
    };

    struct SpiHardwareData
    {
        constexpr SpiHardwareData(const BaseAddr baseAddress, const Byte mosi, const Byte miso, const Byte clk,
                                  const Byte cs0, const Byte cs1, const Byte cs2, const GpioMode pinsMode) :
                                  BASE_ADDRESS(baseAddress), MISO_PIN(miso), MOSI_PIN(mosi), CLK_PIN(clk),
                                  CS0_PIN(cs0), CS1_PIN(cs1), CS2_PIN(cs2), PINS_MODE(pinsMode){}

        BaseAddr BASE_ADDRESS;
        Byte MISO_PIN;
        Byte MOSI_PIN;
        Byte CLK_PIN;
        Byte CS0_PIN;
        Byte CS1_PIN;
        Byte CS2_PIN;
        GpioMode PINS_MODE;
    };

    struct SpiTransferData
    {
        SpiTransferCallback callback = nullptr;
        Byte writeDataLength = 0;
        uint32_t* writeData = nullptr;
        Byte readDataLength = 0;
        uint32_t* readBuffer = nullptr;
    };

}

#endif // __PERIPHERIAL_TYPES__VDYKYY
