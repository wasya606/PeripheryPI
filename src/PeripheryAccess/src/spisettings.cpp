#include "spisettings.h"
#include "common.h"

SpiSettings::SpiSettings() : cs_register(SpiSettings::DEFAULT_CS_REG), clk_register(SpiSettings::DEFAULT_CLK_REG)
{

}

void SpiSettings::setChipSelectPin(const CSPin pin)
{
    cs_register = Common::setBitsByMask(cs_register, Hardware::SPI_CS_CS_MASK, (uint32_t)pin);
}

void SpiSettings::setSpiMode(const SpiMode mode)
{
    cs_register = Common::setBitsByMask(cs_register, Hardware::SPI_CS_CPOL_MASK | Hardware::SPI_CS_CPHA_MASK, (uint32_t)mode);
}

void SpiSettings::setChipSelectPolarity(const CSPin csPin, const SignalPolarity polarity)
{
    BaseBitMask mask = (csPin == CSPin::CS0) ? Hardware::SPI_CS_CSPOL0_MASK : ((csPin == CSPin::CS1) ? Hardware::SPI_CS_CSPOL1_MASK :
                                                                                                       Hardware::SPI_CS_CSPOL2_MASK);

    cs_register = Common::setBitByMask(cs_register, mask, (bool)polarity);
}

void SpiSettings::setDataPolarity(const SignalPolarity polarity)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_CSPOL_MASK, (bool)polarity);
}

void SpiSettings::setBidirectionalMode(const bool isEnabled)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_REN_MASK, isEnabled);
}

void SpiSettings::set_LoSSI_mode_enabled(const bool isEnabled)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_LEN_MASK, isEnabled);
}

void SpiSettings::setInterruptRxNeedRead_enabled(const bool isEnabled)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_INTR_MASK, isEnabled);
}

void SpiSettings::setInterruptDone_enabled(const bool isEnabled)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_INTD_MASK, isEnabled);
}

void SpiSettings::set_DMA_enabled(const bool isEnabled)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_DMAEN_MASK, isEnabled);
}

void SpiSettings::setAutoDeassert_CS_for_DMA(const bool isEnabled)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_ADCS_MASK, isEnabled);
}

void SpiSettings::set_DMA_in_LoSSI_mode_enabled(const bool isEnabled)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_DMA_LEN_MASK, isEnabled);
}

void SpiSettings::set_long_data_word_for_LoSSI_DMA_enabled(const bool isEnabled)
{
    cs_register = Common::setBitByMask(cs_register, Hardware::SPI_CS_LEN_LONG_MASK, isEnabled);
}

void SpiSettings::setClockDivider(const ClockDivider divider)
{
    clk_register = ((uint32_t)divider) & Hardware::SPI_CLK_CDIV_MASK;
}

uint32_t SpiSettings::get_CS_register() const
{
    return cs_register;
}

uint32_t SpiSettings::get_CLK_register() const
{
    return clk_register;
}
