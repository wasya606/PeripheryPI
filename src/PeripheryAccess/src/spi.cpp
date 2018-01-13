#include "spi.h"
#include <sys/mman.h>
#include "hardware.h"
#include "gpio.h"
#include "common.h"

RegAddrPtr SPI::spiMappedAddresses = (RegAddrPtr)MAP_FAILED;
TaskManager SPI::taskManager = TaskManager();

PeripheryInitResult SPI::initSpi()
{
    PeripheryInitResult gpioInitResult = GPIO::initGpio();
    if (!GPIO::isGpioInitialized())
        return gpioInitResult;

    SpiHardwareData spiData = Hardware::SPI_HARDWARE_DATA();
    PeripheryInitResult result = Common::mapPeripheryMemory(spiData.BASE_ADDRESS, spiMappedAddresses);

    if (result != SUCCESS)
        return result;

    if(setupSpiPins() != GPIO_NO_ERRORS)
    {
        Common::unMapPeripheryMemory(spiMappedAddresses);
        return ERROR_SET_SPI_PIN;
    }

    setDefaultSpiSettings();

    return result;
}

PeripheryInitResult SPI::releaseSpi()
{
    Common::unMapPeripheryMemory(spiMappedAddresses);
    resetSpiPins();
    return SUCCESS;
}

SpiAccessResult SPI::setupSpi(const SpiSettings &settings)
{
    if (isSpiInitialized())
    {
        *SPI_CS_REG() = settings.get_CS_register();
        *SPI_CLK_REG() = settings.get_CLK_register();
        return SPI_NO_ERRORS;
    }
    return ERROR_SPI_NOT_INITIALIZED;
}

SpiAccessResult SPI::setupSpi(const Reg32Value csRegister, const Reg32Value clkRegister)
{
    if (isSpiInitialized())
    {
        *SPI_CS_REG() = csRegister;
        *SPI_CLK_REG() = clkRegister;
        return SPI_NO_ERRORS;
    }
    return ERROR_SPI_NOT_INITIALIZED;
}

Reg32Value SPI::get_SPI_CS_register()
{
    return *SPI_CS_REG();
}

Reg32Value SPI::get_SPI_CLK_register()
{
    return *SPI_CLK_REG();
}

GpioAccessResult SPI::resetSpiPins()
{
    SpiHardwareData spiData = Hardware::SPI_HARDWARE_DATA();
    GpioAccessResult setPinModeResult = GPIO::setGpioMode(spiData.CLK_PIN, INPUT);
    if (setPinModeResult == GPIO_NO_ERRORS)
    {
        setPinModeResult = GPIO::setGpioMode(spiData.CS0_PIN, INPUT);
        if (setPinModeResult == GPIO_NO_ERRORS)
        {
            setPinModeResult = GPIO::setGpioMode(spiData.CS1_PIN, INPUT);
            if (setPinModeResult == GPIO_NO_ERRORS)
            {
                setPinModeResult = spiData.CS2_PIN != Hardware::WRONG_PIN ? GPIO::setGpioMode(spiData.CS2_PIN, INPUT) : GPIO_NO_ERRORS;
                if (setPinModeResult == GPIO_NO_ERRORS)
                {
                    setPinModeResult = GPIO::setGpioMode(spiData.MISO_PIN, INPUT);
                    if (setPinModeResult == GPIO_NO_ERRORS)
                        setPinModeResult = GPIO::setGpioMode(spiData.MOSI_PIN, INPUT);
                }
            }
        }
    }

    return setPinModeResult;
}

GpioAccessResult SPI::setupSpiPins()
{
    SpiHardwareData spiData = Hardware::SPI_HARDWARE_DATA();
    GpioAccessResult setPinModeResult = GPIO::setGpioMode(spiData.CLK_PIN, spiData.PINS_MODE);
    if (setPinModeResult == GPIO_NO_ERRORS)
    {
        setPinModeResult = GPIO::setGpioMode(spiData.CS0_PIN, spiData.PINS_MODE);
        if (setPinModeResult == GPIO_NO_ERRORS)
        {
            setPinModeResult = GPIO::setGpioMode(spiData.CS1_PIN, spiData.PINS_MODE);
            if (setPinModeResult == GPIO_NO_ERRORS)
            {
                setPinModeResult = spiData.CS2_PIN != Hardware::WRONG_PIN ? GPIO::setGpioMode(spiData.CS2_PIN, spiData.PINS_MODE) : GPIO_NO_ERRORS;
                if (setPinModeResult == GPIO_NO_ERRORS)
                {
                    setPinModeResult = GPIO::setGpioMode(spiData.MISO_PIN, spiData.PINS_MODE);
                    if (setPinModeResult == GPIO_NO_ERRORS)
                        setPinModeResult = GPIO::setGpioMode(spiData.MOSI_PIN, spiData.PINS_MODE);
                }
            }
        }
    }

    return setPinModeResult;
}


SpiAccessResult SPI::transferData(const uint32_t* writeData, const Byte writeDataLength, const Byte readDataLength,
                                  const SpiTransferCallback callback, uint32_t* readBuffer)
{
    if (!isSpiInitialized())
        return ERROR_SPI_NOT_INITIALIZED;

    SpiTransferData* transferData = new SpiTransferData;
    transferData->writeDataLength = writeDataLength;
    transferData->writeData = (uint32_t*)writeData;
    transferData->readDataLength = readDataLength;
    transferData->readBuffer = readBuffer;
    transferData->callback = callback;

    taskManager.addTask(&doSpiTransfer, (void*)transferData);

    return SPI_NO_ERRORS;
}

SpiAccessResult SPI::addDelayedTransferData(const uint32_t *writeData, const Byte writeDataLength, const Byte readDataLength,
                                            const SpiTransferCallback callback, uint32_t *readBuffer)
{
    if (!isSpiInitialized())
        return ERROR_SPI_NOT_INITIALIZED;

    SpiTransferData* transferData = new SpiTransferData;
    transferData->writeDataLength = writeDataLength;
    transferData->writeData = (uint32_t*)writeData;
    transferData->readDataLength = readDataLength;
    transferData->readBuffer = readBuffer;
    transferData->callback = callback;

    taskManager.addDelayedTask(&doSpiTransfer, (void*)transferData);

    return SPI_NO_ERRORS;
}

void SPI::executeDelayedTransfers()
{
    taskManager.executeDelayedTasks();
}

void SPI::setDefaultSpiSettings()
{
    *SPI_CS_REG() = SpiSettings::DEFAULT_CS_REG;
    *SPI_CLK_REG() = SpiSettings::DEFAULT_CLK_REG;
}

inline bool SPI::isSpiInitialized()
{
    return Common::isAddressMapped(spiMappedAddresses);
}

constexpr RegAddrPtr SPI::SPI_CS_REG(RegAddrPtr mAddr)   { return mAddr + Hardware::SPI_CS_REG_OFFSET;      }
constexpr RegAddrPtr SPI::SPI_FIFO_REG(RegAddrPtr mAddr) { return mAddr + Hardware::SPI_FIFO_REG_OFFSET;    }
constexpr RegAddrPtr SPI::SPI_CLK_REG(RegAddrPtr mAddr)  { return mAddr + Hardware::SPI_CLK_REG_OFFSET;     }


void SPI::doSpiTransfer(const TaskId id, void* data)
{
    SpiTransferData* transferData = (SpiTransferData*)data;

    if (transferData == nullptr)
        return;

    uint32_t* readBuffer = (transferData->readDataLength > 0 && transferData->readBuffer == nullptr) ?
                            new uint32_t[transferData->readDataLength] : transferData->readBuffer;


    Byte writedBlocks = 0;
    Byte readedBlocks = 0;

    //------------------------------------ Start transferring ----------------------------------------------

    //Clear RX and TX FIFO
    *SPI_CS_REG() |= Hardware::SPI_CS_CLEAR_MASK;

    //Set TA (Set the Transfer Active bit of control/status register to '1')
    *SPI_CS_REG() |= Hardware::SPI_CS_TA_MASK;

    while(1)
    {
        //Check for tranfer complete
        if ((*SPI_CS_REG() & Hardware::SPI_CS_DONE_MASK) &&
            (writedBlocks >= transferData->writeDataLength) &&
            (readedBlocks >= transferData->readDataLength))
        {
            //Invoke callback if it exist
            if (transferData->callback != nullptr)
                transferData->callback(id, readBuffer, transferData->readDataLength);

            if (transferData->readDataLength > 0 && transferData->readBuffer == nullptr)
                delete[] readBuffer;
            break;
        }
        else
        {
            //Write data
            if ((writedBlocks == readedBlocks) && (*SPI_CS_REG() & Hardware::SPI_CS_DONE_MASK) &&
                (*SPI_CS_REG() & Hardware::SPI_CS_TXD_MASK))
            {
                *SPI_FIFO_REG() = (writedBlocks < transferData->writeDataLength) ? transferData->writeData[writedBlocks] :
                                                                                   transferData->writeData[transferData->writeDataLength - 1];
                writedBlocks++;
            }

            //Read data
            if ((*SPI_CS_REG() & Hardware::SPI_CS_DONE_MASK) && (*SPI_CS_REG() & Hardware::SPI_CS_RXD_MASK))
            {
                uint32_t readedData = *SPI_FIFO_REG();
                if (readedBlocks < transferData->readDataLength)
                    readBuffer[readedBlocks] = readedData;
                readedBlocks++;
            }
        }
        usleep(10);
    }
    //Clear TA
    *SPI_CS_REG() &= (~Hardware::SPI_CS_TA_MASK);
    delete transferData;
    transferData = nullptr;
    //------------------------------------ Transfer end ----------------------------------------------
}
