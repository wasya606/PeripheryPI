#include "test_mcp3208.h"
#include <iostream>

MCP3208 TestMCP3208::adc = MCP3208();

using namespace std;

void TestMCP3208::testAdc()
{
    cout << "\n\n\tRead ADC\n";
    adc.readChannelRequest(ADC_Channel::CH0, &TestMCP3208::readCallback);
    adc.readChannelRequest(ADC_Channel::CH1, &TestMCP3208::readCallback);
    adc.readChannelRequest(ADC_Channel::CH2, &TestMCP3208::readCallback);
    adc.readChannelRequest(ADC_Channel::CH3, &TestMCP3208::readCallback);
    adc.readChannelRequest(ADC_Channel::CH4, &TestMCP3208::readCallback);
    adc.readChannelRequest(ADC_Channel::CH5, &TestMCP3208::readCallback);
    adc.readChannelRequest(ADC_Channel::CH6, &TestMCP3208::readCallback);
    adc.readChannelRequest(ADC_Channel::CH7, &TestMCP3208::readCallback);

}

void TestMCP3208::readCallback(const TaskId id, const uint32_t* data, const Byte length)
{
    cout << "------------- ADC read Callback id = " << id << "  ---------------\n";
    for (int i = 0; i < length; i++)
    {
        cout << "data[" << i << "] = " << data[i] << endl;
    }
}
