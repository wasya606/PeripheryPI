#ifndef MCP3208_H__VDYKYY___
#define MCP3208_H__VDYKYY___
#include <peripherial_types.h>
#include <list>
#include "taskmanager.h"

enum class ADC_Channel
{
    //Single-ended channels
    CH0 = 0,
    CH1,
    CH2,
    CH3,
    CH4,
    CH5,
    CH6,
    CH7,
    //Differential channels
    DIFF_CH0_P_CH1_N,   //CH0 = IN+, CH1 = IN-
    DIFF_CH0_N_CH1_P,   //CH0 = IN-, CH1 = IN+
    DIFF_CH2_P_CH3_N,   //CH2 = IN+, CH3 = IN-
    DIFF_CH2_N_CH3_P,   //CH2 = IN-, CH3 = IN+
    DIFF_CH4_P_CH5_N,   //CH4 = IN+, CH5 = IN-
    DIFF_CH4_N_CH5_P,   //CH5 = IN-, CH5 = IN+
    DIFF_CH6_P_CH7_N,   //CH6 = IN+, CH7 = IN-
    DIFF_CH6_N_CH7_P    //CH6 = IN-, CH7 = IN+
};

using namespace PeripheralTypes;

class MCP3208
{
public:
    static const constexpr uint16_t ADC_DATA_MASK = 0b0000111111111111;
    static const constexpr uint32_t DEFAULT_READ_INTERVAL = 300; //ms
    static const constexpr uint16_t WRONG_DATA = 0xFFFF;


public:
    MCP3208();
    ~MCP3208();

    void addAllChannelsToCyclicRead();
    void addAllSingleChannelsToCyclicRead();
    void addAllDifferentialToCyclicRead();
    void addChannelsToCyclicRead(const ADC_Channel from, const ADC_Channel to);
    void addChannelToCyclicRead(const ADC_Channel channel);

    void removeAllChannelsFromCyclicRead();
    void removeAllSingleChannelsFromCyclicRead();
    void removeAllDifferentialFromCyclicRead();
    void removeChannelsFromCyclicRead(const ADC_Channel from, const ADC_Channel to);
    void removeChannelFromCyclicRead(const ADC_Channel channel);

    void enableCyclicRead(uint32_t interval = DEFAULT_READ_INTERVAL);
    void disableCyclicRead();
    bool getCyclingReadEnabled();

    const uint16_t* getLastReadedAllChannels() const;
    const uint16_t* getLastReadedAllSingleChannels() const;
    const uint16_t* getLastReadedAllDifferentialChannels() const;
    uint16_t getLastReadedChannel(const ADC_Channel channel) const;
    const uint16_t* getLastReadedChannels(const ADC_Channel from) const;

    void setReadInterval(const uint32_t interval);
    uint32_t getReadInterval();

    TaskId readChannelRequest(const ADC_Channel channel, SpiTransferCallback callback);

    void tmpSerialRead();

private:
    static const constexpr Byte NUM_CHANNELS = (Byte)(ADC_Channel::DIFF_CH6_N_CH7_P) + 1;
    static Byte SPI_COMMANDS[NUM_CHANNELS];

private:
    void spiRequestCallback(const TaskId id, const uint32_t* data, const Byte);
    void cycleDelegate(const TaskId, const TaskParameters);
    void doRequests();
    Byte getIndex(const ADC_Channel channel);

private:
    bool isCyclingReadEnabled;

    Byte tmpSerialIndex;

    uint32_t readInterval;
    Byte pendigRequests;

    uint16_t lastReadedData[NUM_CHANNELS];
    bool cyclicReadChannels[NUM_CHANNELS];
    std::list<Byte> requestedChannels;
    TaskManager timer;
};

#endif // MCP3208_H__VDYKYY___
