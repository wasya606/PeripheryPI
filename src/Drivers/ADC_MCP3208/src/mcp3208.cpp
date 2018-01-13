#include "mcp3208.h"
#include "taskmanager.h"
#include "spi.h"
#include <functional>
#include <iostream>

Byte MCP3208::SPI_COMMANDS[MCP3208::NUM_CHANNELS] = {0b11000, 0b11001, 0b11010, 0b11011, 0b11100, 0b11101, 0b11110, 0b11111,
                                                     0b01000, 0b01001, 0b01010, 0b01011, 0b01100, 0b01101, 0b01110, 0b01111};
using namespace std;
using namespace placeholders;

MCP3208::MCP3208() : isCyclingReadEnabled(false), tmpSerialIndex(0), readInterval(DEFAULT_READ_INTERVAL), pendigRequests(0)
{
    for (Byte i = 0; i < NUM_CHANNELS; i++)
    {
        lastReadedData[i] = WRONG_DATA;
        cyclicReadChannels[i] = false;
    }
}

MCP3208::~MCP3208()
{

}

void MCP3208::addAllChannelsToCyclicRead()
{
    for (Byte i = 0; i < NUM_CHANNELS; i++)
        cyclicReadChannels[i] = true;
}

void MCP3208::addAllSingleChannelsToCyclicRead()
{
    for (Byte i = 0; i <= (Byte)ADC_Channel::CH7; i++)
        cyclicReadChannels[i] = true;
}

void MCP3208::addAllDifferentialToCyclicRead()
{
    for (Byte i = (Byte)ADC_Channel::DIFF_CH0_N_CH1_P; i < NUM_CHANNELS; i++)
        cyclicReadChannels[i] = true;
}

void MCP3208::addChannelsToCyclicRead(const ADC_Channel from, const ADC_Channel to)
{
    for (Byte i = (Byte)from; i <= (Byte)to; i++)
        cyclicReadChannels[i] = true;
}

void MCP3208::addChannelToCyclicRead(const ADC_Channel channel)
{
    cyclicReadChannels[(Byte)channel] = true;
}

void MCP3208::removeAllChannelsFromCyclicRead()
{
    for (Byte i = 0; i < NUM_CHANNELS; i++)
        cyclicReadChannels[i] = false;
}

void MCP3208::removeAllSingleChannelsFromCyclicRead()
{
    for (Byte i = 0; i <= (Byte)ADC_Channel::CH7; i++)
        cyclicReadChannels[i] = false;
}

void MCP3208::removeAllDifferentialFromCyclicRead()
{
    for (Byte i = (Byte)ADC_Channel::DIFF_CH0_N_CH1_P; i < NUM_CHANNELS; i++)
        cyclicReadChannels[i] = false;
}

void MCP3208::removeChannelsFromCyclicRead(const ADC_Channel from, const ADC_Channel to)
{
    for (Byte i = (Byte)from; i <= (Byte)to; i++)
        cyclicReadChannels[i] = false;
}

void MCP3208::removeChannelFromCyclicRead(const ADC_Channel channel)
{
    cyclicReadChannels[(Byte)channel] = false;
}

void MCP3208::enableCyclicRead(uint32_t interval)
{
    isCyclingReadEnabled = true;
    readInterval = interval;
    //doRequests();
    tmpSerialRead();
}

void MCP3208::disableCyclicRead()
{
    isCyclingReadEnabled = false;
}

bool MCP3208::getCyclingReadEnabled()
{
    return isCyclingReadEnabled;
}

const uint16_t *MCP3208::getLastReadedAllChannels() const
{
    return lastReadedData;
}

const uint16_t *MCP3208::getLastReadedAllSingleChannels() const
{
    return lastReadedData;
}

const uint16_t *MCP3208::getLastReadedAllDifferentialChannels() const
{
    return &lastReadedData[(Byte)ADC_Channel::DIFF_CH0_N_CH1_P];
}

uint16_t MCP3208::getLastReadedChannel(const ADC_Channel channel) const
{
    return lastReadedData[(Byte)channel];
}

const uint16_t *MCP3208::getLastReadedChannels(const ADC_Channel from) const
{
    return &lastReadedData[(Byte)from];
}

void MCP3208::setReadInterval(const uint32_t interval)
{
    readInterval = interval;
}

uint32_t MCP3208::getReadInterval()
{
    return readInterval;
}

TaskId MCP3208::readChannelRequest(const ADC_Channel channel, SpiTransferCallback callback)
{
    const Byte index = getIndex(channel);
    uint32_t cmd[1] = {MCP3208::SPI_COMMANDS[index]};
    return SPI::transferData(cmd, 1, 2, callback);
}

void MCP3208::tmpSerialRead()
{
    uint32_t cmd[1] = {SPI_COMMANDS[tmpSerialIndex]};
    cout << "tmpSerialRead(); CMD: " << cmd[0] << ", tmpSerialIndex: " << (int)tmpSerialIndex << endl;
    SPI::addDelayedTransferData(cmd, 1, 2, bind(&MCP3208::spiRequestCallback, this, _1, _2, _3));
    requestedChannels.push_back(tmpSerialIndex);
    tmpSerialIndex = tmpSerialIndex < 15 ? tmpSerialIndex + 1 : 0;
    SPI::executeDelayedTransfers();
}

void MCP3208::spiRequestCallback(const TaskId id, const uint32_t *data, const Byte)
{
    Byte index = requestedChannels.front();
    requestedChannels.pop_front();
    lastReadedData[index] = data[1];

    cout << "spiRequestCallback. ID: " << id << hex << ";  data[0]: " << data[0] << ", data[1]: " << data[1] << dec << endl;

    if (requestedChannels.empty())
        timer.addTask(bind(&MCP3208::cycleDelegate, this, _1, _2), nullptr);
}

void MCP3208::cycleDelegate(const TaskId, const TaskParameters)
{
    usleep(readInterval * 1000);
    cout << "cycleDelegate!!! \n";
    //doRequests();
    tmpSerialRead();
}

void MCP3208::doRequests()
{
    for (Byte i = 0; i < NUM_CHANNELS; i++)
    {
        if (cyclicReadChannels[i])
        {
            uint32_t cmd[1] = {SPI_COMMANDS[i]};
            SPI::addDelayedTransferData(cmd, 1, 2, bind(&MCP3208::spiRequestCallback, this, _1, _2, _3));
            requestedChannels.push_back(i);
        }
    }

    cout << "doRequests(); Has been requested: " << requestedChannels.size() << endl;

    if (requestedChannels.empty())
        timer.addTask(bind(&MCP3208::cycleDelegate, this, _1, _2), nullptr);

    SPI::executeDelayedTransfers();
}

Byte MCP3208::getIndex(const ADC_Channel channel)
{
    return (Byte)channel;
}
