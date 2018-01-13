#ifndef SPI_H_VDYKYY__
#define SPI_H_VDYKYY__

#include <cstddef>
#include "peripherial_types.h"
#include "taskmanager.h"
#include "spisettings.h"
#include "spisettings.h"

using namespace PeripheralTypes;

class SPI
{
public:
    static PeripheryInitResult initSpi();
    static PeripheryInitResult releaseSpi();
    static SpiAccessResult setupSpi(const SpiSettings& settings);
    static SpiAccessResult setupSpi(const Reg32Value csRegister, const Reg32Value clkRegister);

    static Reg32Value get_SPI_CS_register();
    static Reg32Value get_SPI_CLK_register();


    static SpiAccessResult transferData(const uint32_t *writeData, const Byte writeDataLength, const Byte readDataLength = 0,
                                        const SpiTransferCallback callback = nullptr, uint32_t* readBuffer = nullptr);

    static SpiAccessResult addDelayedTransferData(const uint32_t *writeData, const Byte writeDataLength, const Byte readDataLength = 0,
                                                  const SpiTransferCallback callback = nullptr, uint32_t* readBuffer = nullptr);

    static void executeDelayedTransfers();

private:
    static void setDefaultSpiSettings();
    static GpioAccessResult setupSpiPins();
    static GpioAccessResult resetSpiPins();

    static bool isSpiInitialized();
    static inline constexpr RegAddrPtr SPI_CS_REG(RegAddrPtr mAddr = spiMappedAddresses);
    static inline constexpr RegAddrPtr SPI_FIFO_REG(RegAddrPtr mAddr = spiMappedAddresses);
    static inline constexpr RegAddrPtr SPI_CLK_REG(RegAddrPtr mAddr = spiMappedAddresses);
    static void doSpiTransfer(const TaskId id, void *data);

private:
    static RegAddrPtr spiMappedAddresses;

    static TaskManager taskManager;

};

#endif // SPI_H_VDYKYY__
