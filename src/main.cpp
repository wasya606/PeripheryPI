#include "test_app.h"
#include "spi.h"
#include "Menu/menu.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "mcp3208.h"

using namespace std;

TestApp testApp;

void spiTransferCallback(const TaskId id, const uint32_t* data, const Byte length)
{
    cout << "------------- spiTransferCallback id = " << id << "  ---------------\n";
    for (int i = 0; i < length; i++)
    {
        cout << "data[" << i << "] = " << data[i] << endl;
    }
}


int main()
{

    //constexpr Byte WHO_AM_I = 0b10001111;
    //constexpr Byte TEMPERATURE_SENSOR = 0b10100110;
    //constexpr Byte CTL1 = 0b10100000;
    //constexpr Byte CTL1_EN = CTL1 & 0b01111111;
    //constexpr Byte CTL1_EN_XYZT   = 0b00001111;

    //constexpr Byte nRF24L01_REG_MASK = 0b00011111;
    //constexpr Byte nRF24L01_NOP   = 0b11111111;
    //constexpr Byte nRF24L01_READ  = 0b00011111;
    //constexpr Byte nRF24L01_WRITE = 0b00111111;

    //constexpr Byte CAN_STATUS_CMD = 0b10100000;

    SPI::initSpi();
    //sleep(1);

    SpiSettings spiSettings;
    spiSettings.setSpiMode(SpiMode::MODE0);
    spiSettings.setChipSelectPolarity(CSPin::CS0, SignalPolarity::ACTIVE_LOW);
    spiSettings.setDataPolarity(SignalPolarity::ACTIVE_LOW);
    spiSettings.setClockDivider(ClockDivider::DIV256);

    SPI::setupSpi(spiSettings);

    Common::printRegister32(SPI::get_SPI_CS_register());
    Common::printRegister32(SPI::get_SPI_CLK_register());

    testApp.start();


    //uint32_t writeData1[2] = {CTL1_EN, CTL1_EN_XYZT};
    //uint32_t readData1[2];
    //SPI::spiTransferData(writeData1, 2, 20, &spiTransferCallback);
    //uint32_t writeData2[1] = {0b11000};
    //uint32_t readData2[20];
    //SPI::transferData(writeData2, 1, 1, &spiTransferCallback);
    //SPI::spiTransferData(writeData2, 1, 25, &spiTransferCallback);
    //SPI::spiTransferData(writeData2, 1, 3, &spiTransferCallback);



    //MCP3208 adc;

    //adc.addChannelToCyclicRead(ADC_Channel::CH1);
    //adc.addChannelToCyclicRead(ADC_Channel::CH2);
    //adc.addChannelToCyclicRead(ADC_Channel::CH4);

    //adc.readChannelRequest(ADC_Channel::CH0, &spiTransferCallback);
    //adc.readChannelRequest(ADC_Channel::CH1, &spiTransferCallback);
    //adc.readChannelRequest(ADC_Channel::CH2, &spiTransferCallback);

    //adc.enableCyclicRead();



    Menu::getKey();

    return 0;
}

/*
 * void PeripheryAccess::initSD()
{
    TaskManager::addTask();

    //Insert
    setGpioValue(25, HIGH);

    uint32_t init1[12] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    spiTransferByte(init1, 12);

    usleep(10000);

    //Send CMD0 (RESET)
    constexpr Byte CMD_DATA_LEN = 6;
    uint32_t cmd0_data[CMD_DATA_LEN] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};

    setGpioValue(25, LOW);
    spiTransferByte(cmd0_data, CMD_DATA_LEN);

    uint32_t response = 0xFF;
    for (int h = 0; ((response & 0x80) || !(response & 0x1)) && h < 100; h++)
    {
        response = 0xFF;
        spiTransferByte(&response, 1, &onSpiTransferDone);
    }

    usleep(100);
    setGpioValue(25, HIGH);

    cout << "Init SD: " << response << endl;

    //Send CMD1 (INIT)
    setGpioValue(25, LOW);
    if ((response & 0x1))
    {
        for (int i = 0; i < 100; i++)
        {
            uint32_t cmd1_data[CMD_DATA_LEN] = {0x40 | 0x01, 0x00, 0x00, 0x00, 0x00, 0x95};
            spiTransferByte(cmd1_data, CMD_DATA_LEN, &onSpiTransferDone);
        }
    }
    usleep(100);
    setGpioValue(25, HIGH);

    cout << "CMD9 >>>>>>>>>>>>\n";

    //Send CMD9
    uint32_t cmd9_data[CMD_DATA_LEN] = {0x40 | 0x09, 0x00, 0x00, 0x00, 0x00, 0x95};
    setGpioValue(25, LOW);
    spiTransferByte(cmd9_data, CMD_DATA_LEN, &onSpiTransferDone);

    uint32_t cmd9_response[20] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    spiTransferByte(cmd9_response, 20, &onSpiTransferDone);

    usleep(100);
    setGpioValue(25, HIGH);


    cout << "CMD10 >>>>>>>>>>>>\n";

    //Send CMD10
    uint32_t cmd10_data[CMD_DATA_LEN] = {0x40 | 0x0A, 0x00, 0x00, 0x00, 0x00, 0x95};
    setGpioValue(25, LOW);
    spiTransferByte(cmd10_data, CMD_DATA_LEN, &onSpiTransferDone);

    uint32_t cmd10_response[20] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    spiTransferByte(cmd10_response, 20, &onSpiTransferDone);

    usleep(100);
    setGpioValue(25, HIGH);


    cout << "CMD58 >>>>>>>>>>>>\n";

    //Send CMD10
    uint32_t cmd58_data[CMD_DATA_LEN] = {0x40 | 0x3A, 0x00, 0x00, 0x00, 0x00, 0x95};
    setGpioValue(25, LOW);
    spiTransferByte(cmd58_data, CMD_DATA_LEN, &onSpiTransferDone);

    uint32_t cmd58_response[20] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    spiTransferByte(cmd58_response, 20, &onSpiTransferDone);

    usleep(100);
    setGpioValue(25, HIGH);


    usleep(10000);
}

*/
