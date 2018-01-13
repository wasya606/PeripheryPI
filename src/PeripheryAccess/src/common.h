#ifndef COMMON_H
#define COMMON_H
#include <cstddef>
#include "peripherial_types.h"

using namespace PeripheralTypes;
class Common
{
public:
    static PeripheryInitResult mapPeripheryMemory(const BaseAddr hardwareAddress, RegAddrPtr &mappedAddress);
    static bool unMapPeripheryMemory(RegAddrPtr &mappedAddress);

    static bool isAddressMapped(RegAddrPtr mappedAddress);

    static void printRegister32(const uint32_t value);

    static bool getBitByNum(const uint32_t value, const uint8_t bitNum);
    static bool getBitByMask(const uint32_t value, const uint32_t bitMask);

    static uint32_t setBitByNum(const uint32_t value, const uint8_t bitNum, const bool bitValue);
    static uint32_t setBitByMask(const uint32_t value, const uint32_t bitMask, const bool bitValue);

    static uint32_t setBitsByMask(const uint32_t value, const uint32_t bitsMask, uint32_t bitsValue);

    static uint8_t getShiftForMask(uintmax_t mask);

};

#endif // COMMON_H
