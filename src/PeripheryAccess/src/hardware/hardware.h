#ifndef __HARDWARE_H_RPI3__VDYKYY__LUXOFT__
#define __HARDWARE_H_RPI3__VDYKYY__LUXOFT__
#include "peripherial_types.h"

using namespace PeripheralTypes;

class Hardware
{

public:
    //Wrong address
    static const constexpr BaseAddr WRONG_ADDRESS                     = 0xFFFFFFFF;

    static const constexpr Byte WRONG_PIN                             = 0xFF;

    static const constexpr char *DEV_MEM_PATH()                     { return "/dev/mem";}

    //---------------------------- HARDWARE PERIPHERAL CONSTANTS DATA OF RPI3 -----------------------------
    static const constexpr BaseAddr PERIPHERY_BASE_ADDRESS            = 0x3F000000;
    static const constexpr BaseOffset GPIO_BASE_OFFSET                = 0x200000;
    static const constexpr BaseOffset I2C0_BASE_OFFSET                = 0x205000;
    static const constexpr BaseOffset I2C1_BASE_OFFSET                = 0x804000;
    static const constexpr BaseOffset I2C2_BASE_OFFSET                = 0x805000;
    static const constexpr BaseOffset SPI0_BASE_OFFSET                = 0x204000;

    static const constexpr Byte GPIO_REGISTERS_WIDTH                  = 32;           //Bits
    static const constexpr Byte GPIO_COUNT                            = 54;
    static const constexpr Byte I2C_DEVICES_COUNT                     = 3;
    static const constexpr Byte I2C_FIFO_LENGTH                       = 0xF;           //Bytes

    //-------------------------------- Registers OFFSETS ----------------------------------------------------

    //GPIO Mode Registers(Function select)
    static const constexpr RegOffset GPIO_MODE_REGS_OFFSET            = 0x0;
    static const constexpr Byte GPIO_MODE_VALUE_BITS                  = 3;            //Bits

    //GPIO Digital Value Access Registers
    static const constexpr RegOffset GPIO_SET_HIGH_VALUE_OFFSET       = 0x7;          //OFFSET OF FIRST REGISTER FOR SET "HIGH" LEVEL TO GPIO
    static const constexpr RegOffset GPIO_SET_LOW_VALUE_OFFSET        = 0xA;          //OFFSET OF FIRST REGISTER FOR SET "LOW" LEVEL TO GPIO
    static const constexpr RegOffset GPIO_GET_CURRENT_VALUE_OFFSET    = 0xD;          //OFFSET OF FIRST REGISTER FOR GET CURRENT VALUE FROM GPIO
    static const constexpr RegOffset GPIO_LEVEL_VALUE_BITS            = 1;            //Bits

    //+++++++++++++++++++++++++++
    //I2C Registers
    static const constexpr RegOffset  I2C_C_REG_OFFSET                = 0x0;          // C - Register (Control)
    static const constexpr RegOffset  I2C_S_REG_OFFSET                = 0x1;          // S - Register (Status)
    static const constexpr RegOffset  I2C_DLEN_REG_OFFSET             = 0x2;          // DLEN - Register (Data Length)
    static const constexpr RegOffset  I2C_A_REG_OFFSET                = 0x3;          // A - Register (Slave address)
    static const constexpr RegOffset  I2C_FIFO_REG_OFFSET             = 0x4;          // FIFO - Register (Data buffer)
    static const constexpr RegOffset  I2C_DIV_REG_OFFSET              = 0x5;          // DIV - Register (Clock Divider )
    static const constexpr RegOffset  I2C_DEL_REG_OFFSET              = 0x6;          // DEL - Register (Data Delay)
    static const constexpr RegOffset  I2C_CLKT_REG_OFFSET             = 0x7;          // CLKT - Register (Clock Stretch Timeout)

    //+++++++++++++++++++++++++++
    //SPI Registers
    static const constexpr RegOffset  SPI_CS_REG_OFFSET               = 0x0;          // CS - Register (Control and Status)
    static const constexpr RegOffset  SPI_FIFO_REG_OFFSET             = 0x1;          // FIFO - Register (TX and RX Data buffers)
    static const constexpr RegOffset  SPI_CLK_REG_OFFSET              = 0x2;          // CLK - Register (Clock Divider)
    static const constexpr RegOffset  SPI_DLEN_REG_OFFSET             = 0x3;          // DLEN - Register (Data Length)
    static const constexpr RegOffset  SPI_LTOH_REG_OFFSET             = 0x4;         // LTOH - Register (LOSSI mode TOH)
    static const constexpr RegOffset  SPI_DC_REG_OFFSET               = 0x5;         // DC - Register (DMA DREQ Controls)


    //-------------------------------- Registers BIT MASKS ----------------------------------------------------

    //I2C Control Register Bit Masks(C - Register)
    static const constexpr BaseBitMask I2C_C_I2CEN_MASK               = 1 << 15;      // I2CEN;   RW;     0x0
    static const constexpr BaseBitMask I2C_C_INTR_MASK                = 1 << 10;      // INTR;    RW;     0x0
    static const constexpr BaseBitMask I2C_C_INTT_MASK                = 1 << 9;       // INTT;    RW;     0x0
    static const constexpr BaseBitMask I2C_C_INTD_MASK                = 1 << 8;       // INTD;    RW;     0x0
    static const constexpr BaseBitMask I2C_C_ST_MASK                  = 1 << 7;       // ST;      RW;     0x0
    static const constexpr BaseBitMask I2C_C_CLEAR_MASK               = (1 << 4) |
                                                                        (1 << 5);     // CLEAR;   RW;     0x0
    static const constexpr BaseBitMask I2C_C_READ_MASK                = 1 << 0;       // READ;    RW;     0x0

    //I2C Status Register Bit Masks(S - Register)
    static const constexpr BaseBitMask I2C_S_CLKT_MASK                = 1 << 9;       // CLKT;    RW;     0x0
    static const constexpr BaseBitMask I2C_S_ERR_MASK                 = 1 << 8;       // ERR;     RW;     0x0
    static const constexpr BaseBitMask I2C_S_RXF_MASK                 = 1 << 7;       // RXF;     RO;     0x0
    static const constexpr BaseBitMask I2C_S_TXE_MASK                 = 1 << 6;       // TXE;     RO;     0x1
    static const constexpr BaseBitMask I2C_S_RXD_MASK                 = 1 << 5;       // RXD;     RO;     0x0
    static const constexpr BaseBitMask I2C_S_TXD_MASK                 = 1 << 4;       // TXD;     RO;     0x1
    static const constexpr BaseBitMask I2C_S_RXR_MASK                 = 1 << 3;       // RXR;     RO;     0x0
    static const constexpr BaseBitMask I2C_S_TXW_MASK                 = 1 << 2;       // TXW;     RO;     0x0
    static const constexpr BaseBitMask I2C_S_DONE_MASK                = 1 << 1;       // DONE;    RW;     0x0
    static const constexpr BaseBitMask I2C_S_TA_MASK                  = 1 << 0;       // TA;      RO;     0x0

    //I2C Data Lenght Register Bit Masks(DLEN - Register)
    static const constexpr BaseBitMask I2C_DLEN_DLEN_MASK             = 0x0000FFFF;   // DLEN;    RW;     0x00

    //I2C Slave Address Register Bit Masks(A - Register)
    static const constexpr BaseBitMask I2C_A_ADDR_MASK                = 0x0000007F;   // ADDR;    RW;     0x00

    //I2C FIFO Register Bit Masks(FIFO - Register)
    static const constexpr BaseBitMask I2C_FIFO_DATA_MASK             = 0x000000FF;   // DATA;    RW;     0x00

    //I2C Clock Divider Register Bit Masks(DIV - Register)
    static const constexpr BaseBitMask I2C_DIV_CDIV_MASK              = 0x0000FFFF;   // CDIV;    RW;     0x5DC

    //I2C Data Delay Register Bit Masks(DEL - Register)
    static const constexpr BaseBitMask I2C_DEL_FEDL_MASK              = 0xFFFF0000;   // FEDL;    RW;     0x30
    static const constexpr BaseBitMask I2C_DEL_REDL_MASK              = 0x0000FFFF;   // REDL;    RW;     0x30

    //I2C Clock Stretch Timeout Register Bit Masks(CLKT - Register)
    static const constexpr BaseBitMask I2C_CLKT_TOUT_MASK             = 0x0000FFFF;   // TOUT;    RW;     0x40

    //+++++++++++++++++++++++++++
    //SPI Control/Status Register Bit Masks(CS - Register)
    static const constexpr BaseBitMask SPI_CS_LEN_LONG_MASK           = 1 << 25;      //LEN_LONG; RW;     0x0
    static const constexpr BaseBitMask SPI_CS_DMA_LEN_MASK            = 1 << 24;      // DMA_LEN; RW;     0x0
    static const constexpr BaseBitMask SPI_CS_CSPOL2_MASK             = 1 << 23;      // CSPOL2;  RW;     0x0
    static const constexpr BaseBitMask SPI_CS_CSPOL1_MASK             = 1 << 22;      // CSPOL1;  RW;     0x0
    static const constexpr BaseBitMask SPI_CS_CSPOL0_MASK             = 1 << 21;      // CSPOL0;  RW;     0x0
    static const constexpr BaseBitMask SPI_CS_RXF_MASK                = 1 << 20;      // RXF;     RO;     0x0
    static const constexpr BaseBitMask SPI_CS_RXR_MASK                = 1 << 19;      // RXR;     RO;     0x0
    static const constexpr BaseBitMask SPI_CS_TXD_MASK                = 1 << 18;      // TXD;     RO;     0x1
    static const constexpr BaseBitMask SPI_CS_RXD_MASK                = 1 << 17;      // RXD;     RO;     0x0
    static const constexpr BaseBitMask SPI_CS_DONE_MASK               = 1 << 16;      // DONE;    RO;     0x0
    static const constexpr BaseBitMask SPI_CS_TE_EN_MASK              = 1 << 15;      // TE_EN;   RW;     0x0
    static const constexpr BaseBitMask SPI_CS_LMONO_MASK              = 1 << 14;      // LMONO;   RW;     0x0
    static const constexpr BaseBitMask SPI_CS_LEN_MASK                = 1 << 13;      // LEN;     RW;     0x0
    static const constexpr BaseBitMask SPI_CS_REN_MASK                = 1 << 12;      // REN;     RW;     0x1
    static const constexpr BaseBitMask SPI_CS_ADCS_MASK               = 1 << 11;      // ADCS;    RW;     0x0
    static const constexpr BaseBitMask SPI_CS_INTR_MASK               = 1 << 10;      // INTR;    RW;     0x0
    static const constexpr BaseBitMask SPI_CS_INTD_MASK               = 1 << 9;       // INTD;    RW;     0x0
    static const constexpr BaseBitMask SPI_CS_DMAEN_MASK              = 1 << 8;       // DMAEN;   RW;     0x0
    static const constexpr BaseBitMask SPI_CS_TA_MASK                 = 1 << 7;       // TA;      RW;     0x0
    static const constexpr BaseBitMask SPI_CS_CSPOL_MASK              = 1 << 6;       // CSPOL;   RW;     0x0
    static const constexpr BaseBitMask SPI_CS_CLEAR_MASK              = 0x00000030;   // CLEAR;   RW;     0x0
    static const constexpr BaseBitMask SPI_CS_CPOL_MASK               = 1 << 3;       // CPOL;    RW;     0x0
    static const constexpr BaseBitMask SPI_CS_CPHA_MASK               = 1 << 2;       // CPOL;    RW;     0x0
    static const constexpr BaseBitMask SPI_CS_CS_MASK                 = 0x00000003;   // CS;      RW;     0x0

    //SPI FIFO Register Bit Masks(FIFO - Register)
    static const constexpr BaseBitMask SPI_FIFO_DATA_MASK             = 0xFFFFFFFF;   // DATA;    RW;     0x0

    //SPI CLK Register Bit Masks(CLK - Register)
    static const constexpr BaseBitMask SPI_CLK_CDIV_MASK              = 0x0000FFFF;   // CDIV;    RW;     0x0

    //SPI DLEN Register Bit Masks(DLEN - Register)
    static const constexpr BaseBitMask SPI_DLEN_LEN_MASK              = 0x0000FFFF;   // LEN;     RW;     0x0

    //SPI LTOH Register Bit Masks(LTOH - Register)
    static const constexpr BaseBitMask SPI_LTOH_TOH_MASK              = 0x0000000F;   // TOH;     RW;     0x1

    //SPI DC Register Bit Masks(DC - Register)
    static const constexpr BaseBitMask SPI_DC_RPANIC_MASK             = 0xFF000000;   // RPANIC;  RW;     0x30
    static const constexpr BaseBitMask SPI_DC_RDREQ_MASK              = 0x00FF0000;   // RDREQ;   RW;     0x20
    static const constexpr BaseBitMask SPI_DC_TPANIC_MASK             = 0x0000FF00;   // TPANIC;  RW;     0x10
    static const constexpr BaseBitMask SPI_DC_TDREQ_MASK              = 0x000000FF;   // TDREQ;   RW;     0x20


    //-------------------------------- COMPILE TIME CALCULATED PERIPHERAL DATA ------------------------------
    static const constexpr BaseAddr GPIO_BASE_ADDRESS                 = PERIPHERY_BASE_ADDRESS + GPIO_BASE_OFFSET;
    static const constexpr BaseAddr I2C0_BASE_ADDRESS                 = PERIPHERY_BASE_ADDRESS + I2C0_BASE_OFFSET;
    static const constexpr BaseAddr I2C1_BASE_ADDRESS                 = PERIPHERY_BASE_ADDRESS + I2C1_BASE_OFFSET;
    static const constexpr BaseAddr I2C2_BASE_ADDRESS                 = PERIPHERY_BASE_ADDRESS + I2C2_BASE_OFFSET;

    static const constexpr BaseAddr SPI0_BASE_ADDRESS                 = PERIPHERY_BASE_ADDRESS + SPI0_BASE_OFFSET;

    static const constexpr Byte  GPIO_MODE_VALUES_PER_REG             = GPIO_REGISTERS_WIDTH / GPIO_MODE_VALUE_BITS;
    static const constexpr Byte  GPIO_LEVEL_VALUES_PER_REG            = GPIO_REGISTERS_WIDTH / GPIO_LEVEL_VALUE_BITS;

    //-----------------------------------------  GPIO ACCESS FUNCTIONS ------------------------------------------------
    static inline constexpr RegAddrPtr GPIO_MODE_REG_ADDRESS(const Byte gpioNum, BaseAddrPtr mappedGpioAddress);
    static inline constexpr RegAddrPtr GPIO_SET_HIGH_VALUE_REG_ADDRESS(const Byte gpioNum, BaseAddrPtr mappedGpioAddress);
    static inline constexpr RegAddrPtr GPIO_SET_LOW_VALUE_REG_ADDRESS(const Byte gpioNum, BaseAddrPtr mappedGpioAddress);
    static inline constexpr RegAddrPtr GPIO_GET_VALUE_REG_ADDRESS(const Byte gpioNum, BaseAddrPtr mappedGpioAddress);
    static inline constexpr BaseBitMask GPIO_MODE_BIT0_MASK(const Byte gpioNum);
    static inline constexpr BaseBitMask GPIO_MODE_BITS_MASK(const Byte gpioNum);
    static inline constexpr BaseBitMask GPIO_VALUE_BIT_MASK(const Byte gpioNum);

    //-----------------------------------------  I2C ACCESS FUNCTIONS ------------------------------------------------
    static inline constexpr I2cHardwareData I2C_HARDWARE_DATA(const Byte i2cDevice);

    //-----------------------------------------  SPI ACCESS FUNCTIONS ------------------------------------------------
    static inline constexpr SpiHardwareData SPI_HARDWARE_DATA();

};

#include "hardware.hpp"

#endif // __HARDWARE_H_RPI3__VDYKYY__LUXOFT__
