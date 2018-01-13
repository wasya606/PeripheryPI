#ifndef SPISETTINGS_H
#define SPISETTINGS_H
#include <cstdint>
#include "hardware.h"

enum class CSPin
{
    CS0 = 0b00,
    CS1 = 0b01,
    CS2 = 0b10,
    NO_CS = 0b11
};

enum class SignalPolarity
{
    ACTIVE_LOW = 0,
    ACTIVE_HIGH = 1
};

enum class SpiMode
{
    MODE0 = 0b00,
    MODE1 = 0b01,
    MODE2 = 0b10,
    MODE3 = 0b11
};

enum class ClockDivider
{
    DIV0        = 0x0,
    DIV1        = 0x1,
    DIV2        = 0x2,
    DIV4        = 0x4,
    DIV8        = 0x8,
    DIV16       = 0x10,
    DIV32       = 0x20,
    DIV64       = 0x40,
    DIV128      = 0x80,
    DIV256      = 0x100,
    DIV512      = 0x200,
    DIV1024     = 0x400,
    DIV2048     = 0x800,
    DIV4096     = 0x1000,
    DIV8192     = 0x2000,
    DIV16384    = 0x4000,
    DIV32768    = 0x8000,
    DIV65536    = 0x10000
};

class SpiSettings
{
public:
    static const constexpr uint32_t DEFAULT_CS_REG  = 0x00040040; // MODE0, CS0, CSPOL = 1
    static const constexpr uint32_t DEFAULT_CLK_REG = 0x00000200; // CDIV = 512

public:
    SpiSettings();

    void setChipSelectPin(const CSPin pin);
    void setSpiMode(const SpiMode mode);
    void setChipSelectPolarity(const CSPin csPin, const SignalPolarity polarity);
    void setDataPolarity(const SignalPolarity polarity);
    void setBidirectionalMode(const bool isEnabled);
    void set_LoSSI_mode_enabled(const bool isEnabled);
    void setInterruptRxNeedRead_enabled(const bool isEnabled);
    void setInterruptDone_enabled(const bool isEnabled);
    void set_DMA_enabled(const bool isEnabled);
    void setAutoDeassert_CS_for_DMA(const bool isEnabled);
    void set_DMA_in_LoSSI_mode_enabled(const bool isEnabled);
    void set_long_data_word_for_LoSSI_DMA_enabled(const bool isEnabled);

    void setClockDivider(const ClockDivider divider);

    uint32_t get_CS_register() const;
    uint32_t get_CLK_register() const;

private:
    uint32_t cs_register;
    uint32_t clk_register;
};

#endif // SPISETTINGS_H
