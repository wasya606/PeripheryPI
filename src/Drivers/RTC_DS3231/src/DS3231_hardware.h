#ifndef __DS3231_HARDWARE_H__VDYKYY
#define __DS3231_HARDWARE_H__VDYKYY
#include "rtc_types.h"

//------------------  DS3231 Hardware data ---------------------//
//----- For details see ""../Docs/DataSheets/DS3231M.pdf"-------//

//DS3231 I2C bus address
static const constexpr Reg8Addr I2C_ADDR                        = 0x68;

//********* DS3231 REGISTERS *********//

//Geberal Date/Time Registers of DS3231
static const constexpr Reg8Addr SECONDS_REGISTER                = 0x00;
static const constexpr Reg8Addr MINUTES_REGISTER                = 0x01;
static const constexpr Reg8Addr HOURS_REGISTER                  = 0x02;
static const constexpr Reg8Addr DAY_REGISTER                    = 0x03; //Day of week (1 - 7)
static const constexpr Reg8Addr DATE_REGISTER                   = 0x04; //Day of month (1 - 31)
static const constexpr Reg8Addr MONTH_REGISTER                  = 0x05;
static const constexpr Reg8Addr YEAR_REGISTER                   = 0x06;

//Alarm1 Date/Time Registers of DS3231
static const constexpr Reg8Addr ALARM1_SECONDS_REG              = 0x07;
static const constexpr Reg8Addr ALARM1_MINUTES_REG              = 0x08;
static const constexpr Reg8Addr ALARM1_HOURS_REG                = 0x09;
static const constexpr Reg8Addr ALARM1_DAY_DATE_REG             = 0x0A;

//Alarm2 Date/Time Registers of DS3231
static const constexpr Reg8Addr ALARM2_MINUTES_REG              = 0x0B;
static const constexpr Reg8Addr ALARM2_HOURS_REG                = 0x0C;
static const constexpr Reg8Addr ALARM2_DAY_DATE_REG             = 0x0D;
//Control Register
static const constexpr Reg8Addr CONTROL_REGISTER                = 0x0E;

//Status Register
static const constexpr Reg8Addr STATUS_REGISTER                 = 0x0F;

//Aging Offset Register
static const constexpr Reg8Addr AGING_OFFSET_REGISTER           = 0x10;

//Temperature MSB Register
static const constexpr Reg8Addr MSB_REGISTER                    = 0x07;

//Temperature LSB Register
static const constexpr Reg8Addr LSB_REGISTER                    = 0x07;
//********************************//

//********* DS3231 REGISTERS DETAILS *********//
//SECONDS_REGISTER details
static const constexpr Reg8BitMask SECONDS_MASK                 = 0b00001111;
static const constexpr Reg8BitMask SECONDS_DOZENS_MASK          = 0b01110000;

//MINUTES_REGISTER details
static const constexpr Reg8BitMask MINUTES_MASK                 = 0b00001111;
static const constexpr Reg8BitMask MINUTES_DOZENS_MASK          = 0b01110000;

//HOURS_REGISTER details
static const constexpr Reg8BitMask HOURS_MASK                   = 0b00001111;
static const constexpr Reg8BitMask HOURS_DOZENS_MASK            = 0b00010000;
static const constexpr Reg8BitMask HOURS_TWENTIES_MASK          = 0b00100000; // Twenties of hour only for 24H mode(see below)
static const constexpr Reg8BitMask HOURS_AM_PM_FLAG_MASK        = 0b00100000; // AM/PM flag only for 12H mode(see below)
static const constexpr Reg8BitMask HOURS_12_24_MODE_MASK        = 0b01000000; // Set to "1" for 24H mode and to "0" for 12H mode

//DAY_REGISTER details
static const constexpr Reg8BitMask DAY_OF_WEEK_MASK             = 0b00000111; // Day of week (1 - 7)

//DATE_REGISTER details
static const constexpr Reg8BitMask DATE_DAY_MASK                = 0b00001111; // Date day % 10 (1 - 9)
static const constexpr Reg8BitMask DATE_DAY_DOZENS_MASK         = 0b00110000; // Date day / 10 (0 - 3)

//MONTH_REGISTER details
static const constexpr Reg8BitMask MONTH_MASK                   = 0b00001111; // Month % 10 (1 - 9)
static const constexpr Reg8BitMask MONTH_DOZENS_MASK            = 0b00010000; // Month / 10 (0 - 1)
static const constexpr Reg8BitMask CENTURY_MASK                 = 0b10000000;

//YEAR_REGISTER details
static const constexpr Reg8BitMask YEAR_MASK                    = 0b00001111;
static const constexpr Reg8BitMask YEAR_DOZENS_MASK             = 0b11110000;

//-------------------

//ALARM1_SECONDS_REGISTER details
static const constexpr Reg8BitMask A1_SECONDS_MASK              = 0b00001111;
static const constexpr Reg8BitMask A1_SECONDS_DOZENS_MASK       = 0b01110000;
static const constexpr Reg8BitMask A1_M1_MASK                   = 0b10000000;

//ALARM1_MINUTES_REGISTER details
static const constexpr Reg8BitMask A1_MINUTES_MASK              = 0b00001111;
static const constexpr Reg8BitMask A1_MINUTES_DOZENS_MASK       = 0b01110000;
static const constexpr Reg8BitMask A1_M2_MASK                   = 0b10000000;

//ALARM1_HOURS_REGISTER details
static const constexpr Reg8BitMask A1_HOURS_MASK                = 0b00001111;
static const constexpr Reg8BitMask A1_HOURS_DOZENS_MASK         = 0b00010000;
static const constexpr Reg8BitMask A1_HOURS_TWENTIES_MASK       = 0b00100000; // Twenties of hour only for 24H mode(see below)
static const constexpr Reg8BitMask A1_HOURS_AM_PM_FLAG_MASK     = 0b00100000; // AM/PM flag only for 12H mode(see below)
static const constexpr Reg8BitMask A1_HOURS_12_24_MODE_MASK     = 0b01000000; // Set to "1" for 24H mode and to "0" for 12H mode
static const constexpr Reg8BitMask A1_M3_MASK                   = 0b10000000;

//ALARM1_DAY_DATE_REG_REGISTER details
static const constexpr Reg8BitMask A1_DAY_MASK                  = 0b00001111; //Day of week (1 - 7) only for DAY mode
static const constexpr Reg8BitMask A1_DATE_MASK                 = 0b00001111; //Date % 10 (1 - 9) only for DATE mode
static const constexpr Reg8BitMask A1_DATE_DAY_DOZENS_MASK      = 0b00110000; //Date / 10 (0 - 3) only for DATE mode
static const constexpr Reg8BitMask A1_DAY_DATE_MODE_MASK        = 0b01000000; // Set to "1" for DAY mode and to "0" for DATE mode
static const constexpr Reg8BitMask A1_M4_MASK                   = 0b10000000;

//-------------------

//ALARM2_MINUTES_REGISTER details
static const constexpr Reg8BitMask A2_MINUTES_MASK              = 0b00001111;
static const constexpr Reg8BitMask A2_MINUTES_DOZENS_MASK       = 0b01110000;
static const constexpr Reg8BitMask A2_M2_MASK                   = 0b10000000;

//ALARM2_HOURS_REGISTER details
static const constexpr Reg8BitMask A2_HOURS_MASK                = 0b00001111;
static const constexpr Reg8BitMask A2_HOURS_DOZENS_MASK         = 0b00010000;
static const constexpr Reg8BitMask A2_HOURS_TWENTIES_MASK       = 0b00100000; // Twenties of hour only for 24H mode(see below)
static const constexpr Reg8BitMask A2_HOURS_AM_PM_FLAG_MASK     = 0b00100000; // AM/PM flag only for 12H mode(see below)
static const constexpr Reg8BitMask A2_HOURS_12_24_MODE_MASK     = 0b01000000; // Set to "1" for 24H mode and to "0" for 12H mode
static const constexpr Reg8BitMask A2_M3_MASK                   = 0b10000000;

//ALARM2_DAY_DATE_REG_REGISTER details
static const constexpr Reg8BitMask A2_DAY_MASK                  = 0b00001111; //Day of week (1 - 7) only for DAY mode
static const constexpr Reg8BitMask A2_DATE_MASK                 = 0b00001111; //Date % 10 (1 - 9) only for DATE mode
static const constexpr Reg8BitMask A2_DATE_DAY_DOZENS_MASK      = 0b00110000; //Date / 10 (0 - 3) only for DATE mode
static const constexpr Reg8BitMask A2_DAY_DATE_MODE_MASK        = 0b01000000; // Set to "1" for DAY mode and to "0" for DATE mode
static const constexpr Reg8BitMask A2_M4_MASK                   = 0b10000000;

//-------------------

//CONTROL_REGISTER details
static const constexpr Reg8BitMask CONTROL_NOT_EOSCT_MASK       = 0b10000000;
static const constexpr Reg8BitMask CONTROL_BBSQW_MASK           = 0b01000000;
static const constexpr Reg8BitMask CONTROL_CONV_MASK            = 0b00100000;
static const constexpr Reg8BitMask CONTROL_INTCN_MASK           = 0b00000100;
static const constexpr Reg8BitMask CONTROL_A2IE_MASK            = 0b00000010;
static const constexpr Reg8BitMask CONTROL_A1IE_MASK            = 0b00000001;

//STATUS_REGISTER details
static const constexpr Reg8BitMask STATUS_OSF_MASK              = 0b10000000;
static const constexpr Reg8BitMask STATUS_EN32KHZ_MASK          = 0b00001000;
static const constexpr Reg8BitMask STATUS_BSY_MASK              = 0b00000100;
static const constexpr Reg8BitMask STATUS_A2F_MASK              = 0b00000010;
static const constexpr Reg8BitMask STATUS_A1F_MASK              = 0b00000001;

//AGING_OFFSET_REGISTER details
static const constexpr Reg8BitMask AGING_SIGN_MASK              = 0b10000000;
static const constexpr Reg8BitMask AGING_DATA_MASK              = 0b01111111;

//MSB_REGISTER details
static const constexpr Reg8BitMask MSB_SIGN_MASK                = 0b10000000;
static const constexpr Reg8BitMask MSB_DATA_MASK                = 0b01111111;

//LSB_REGISTER details
static const constexpr Reg8BitMask LSB_DATA_MASK                = 0b11000000;


#endif // __DS3231_HARDWARE_H__VDYKYY
