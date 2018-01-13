#include "common.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "hardware.h"

using namespace std;

PeripheryInitResult Common::mapPeripheryMemory(const BaseAddr hardwareAddress, RegAddrPtr &mappedAddress)
{
    if (mappedAddress != (RegAddrPtr)MAP_FAILED && mappedAddress != nullptr)
        unMapPeripheryMemory(mappedAddress);

    int fd_mem = -1;
    if ((fd_mem = open(Hardware::DEV_MEM_PATH(), O_RDWR | O_SYNC)) < 0)
        return ERROR_OPEN_MEM_DEV;

    BaseAddrPtr peripheryMappedAddress = (BaseAddrPtr)mmap(nullptr, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem, hardwareAddress);
    if (peripheryMappedAddress != nullptr && peripheryMappedAddress == MAP_FAILED)
        return ERROR_MEM_MAP;

    mappedAddress = (BaseAddrPtr)peripheryMappedAddress;
    close(fd_mem);
    return SUCCESS;
}

bool Common::unMapPeripheryMemory(RegAddrPtr &mappedAddress)
{
    if (mappedAddress != nullptr && mappedAddress != (RegAddrPtr)MAP_FAILED)
    {
        munmap((void* )mappedAddress, getpagesize());
        mappedAddress = (RegAddrPtr)MAP_FAILED;
        return true;
    }
    return false;
}

bool Common::isAddressMapped(RegAddrPtr mappedAddress)
{
    return mappedAddress != (RegAddrPtr)MAP_FAILED && mappedAddress != nullptr;
}

void Common::printRegister32(const uint32_t value)
{
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "|31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|\n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "|";
    for (int i = 31; i >= 0 ; i--)
        cout << "`" << getBitByNum(value, i) << "|";

    cout << "\n------------------------------------------------------------------------------------------------\n";
    cout << "HEX value: 0x" << hex << value << "\nDEC value: " << dec << value;
    cout << "\n------------------------------------------------------------------------------------------------\n";
}

bool Common::getBitByNum(const uint32_t value, const uint8_t bitNum)
{
    return getBitByMask(value, 1 << bitNum);
}

bool Common::getBitByMask(const uint32_t value, const uint32_t bitMask)
{
    return value & bitMask;
}

uint32_t Common::setBitByNum(const uint32_t value, const uint8_t bitNum, const bool bitValue)
{
    return setBitByMask(value, 1 << bitNum, bitValue);
}

uint32_t Common::setBitByMask(const uint32_t value, const uint32_t bitMask, const bool bitValue)
{
    uint32_t result = value;
    if (bitValue)
        result |= bitMask;
    else
        result &= (~bitMask);

    return result;
}

uint32_t Common::setBitsByMask(const uint32_t value, const uint32_t bitsMask, uint32_t bitsValue)
{
    return (value & ~bitsMask) | (bitsValue << getShiftForMask(bitsMask));
}

uint8_t Common::getShiftForMask(uintmax_t mask)
{
#ifdef __GNUC__
    return __builtin_ctz(mask);
#else
    uint8_t result = 0;
    while(mask % 2 == 0)
    {
        mask >>= 1;
        result++;
    }
    return result;
#endif
}


