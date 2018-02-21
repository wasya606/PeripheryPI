#include "test_app.h"
#include <functional>
#include <iostream>
#include <cstring>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <unistd.h>
#include "test_mcp3208.h"

#define LED1_GPIO_PIN 5
#define LED2_GPIO_PIN 6
#define BUZZER_GPIO_PIN 23

using namespace std;
using namespace placeholders;


TestApp::TestApp() : menu(nullptr)
{
    createMenu();
    initPeriphery();
}

TestApp::~TestApp()
{
    if (menu != nullptr)
        delete menu;
}

void TestApp::start()
{
    bool needUpdate = true;
    do
    {
        if (needUpdate)
            updateMenu();

        needUpdate = menu->processStep(Menu::getKey());
    }
    while (1);
}

void TestApp::createMenu()
{
    menu = new Menu("********** PERIPERY LIBRARY MINI TEST **********", bind(&TestApp::mainMenuHandler, this, _1));
    menu->pushItem("-------------- GPIO -------------", true);
    menu->pushItem("Write \"HIGH\" to GPIO #5        ");
    menu->pushItem("Write \"LOW\" to GPIO #5         ");
    menu->pushItem("Read from GPIO #6                ");
    menu->pushItem("------ RTC DS3231 (I2C1) --------", true);
    menu->pushItem("Show Date/Time from RTC(I2C1)    ");
    menu->pushItem("Write system Date/Time to RTC    ");
    menu->pushItem("--------- EEPROM 24Cxx ----------", true);
    menu->pushItem("Read from EEPROM on I2C0 (ASCII) ");
    menu->pushItem("Read from EEPROM on I2C0 (RAW)   ");
    menu->pushItem("Write to EEPROM  on I2C0 (ASCII) ");
    menu->pushItem("Write to EEPROM  on I2C0 (RAW)   ");
    menu->pushItem("------  ADC MCP3208 (SPI0) ------", true);
    menu->pushItem("Read ADC channels                ");
    menu->pushItem("---------------------------------", true);
    menu->pushItem("Exit                             ");

    menu->resetActiveItem();
}

void TestApp::mainMenuHandler(MenuItem *item)
{
    switch (item->getId())
    {
        case 0:
        {
            //GPIO TITLE. DO NOTHING
            break;
        }
        case 1://Write "HIGH" to GPIO
        {
            Menu::clearScreen();
            TestGpio::writeGpio5(true);
            showResult();
            break;
        }
        case 2://Write "LOW" to GPIO
        {
            Menu::clearScreen();
            TestGpio::writeGpio5(false);
            showResult();
            break;
        }
        case 3://Read GPIO
        {
            Menu::clearScreen();
            TestGpio::readGpio6();
            showResult();
            break;
        }
        case 4:
        {
            //RTC DS3231 (I2C1) TITLE. DO NOTHING
            break;
        }
        case 5://Show Date/Time from RTC(I2C1)
        {
            Menu::clearScreen();
            outCurrentRtcDateTime();
            showResult();
            break;
        }
        case 6://Write system Date/Time to RTC
        {
            Menu::clearScreen();
            setRtcFromLocalDateTime();
            cout << "\n\n\t RTC DATE/TIME UPDATED FROM SYSTEM DATE!!!\n";
            outCurrentRtcDateTime();
            showResult("RTC has been writed from system time!");
            break;
        }
        case 7:
        {
            //EEPROM 24Cxx TITLE. DO NOTHING
            break;
        }
        case 8://Read from EEPROM on I2C0 (ASCII)
        {
            Menu::clearScreen();
            readEEPROM();
            showResult();
            break;
        }
        case 9://Read from EEPROM on I2C0 (RAW)
        {
            Menu::clearScreen();
            readEEPROM(false);
            showResult();
            break;
        }
        case 10://Write to EEPROM  on I2C0 (ASCII)
        {
            Menu::clearScreen();
            writeEEPROM();
            showResult();
            break;
        }
        case 11://"Write to EEPROM  on I2C0 (RAW)
        {
            Menu::clearScreen();
            showResult("Not implemented yet\n");
            break;
        }
        case 12:
        {
            //ADC MCP3208 (SPI0) TITLE. DO NOTHING
            break;
        }
        case 13://Read ADC channels
        {
            Menu::clearScreen();
            TestMCP3208::testAdc();
            showResult();
            break;
        }
        case 14:
        {
            //TITLE. DO NOTHING
            break;
        }
        case 15:
        {
            exit(0);
            break;
        }

        default:
            break;
    }
}

void TestApp::updateMenu()
{
    Menu::clearScreen();

    cout << endl << endl << "\t" << menu->getTitle() << endl << endl;
    for (size_t i = 0; i < menu->getSize(); i++)
    {
        char* name = menu->getItem(i)->getName();
        size_t nameLen = strlen(name);
        size_t activeItem = menu->getActiveItemId();
        if (activeItem == i)
        {
            cout << "\t";
            repeatText("=", nameLen + 6);
            cout << "\t|  " << menu->getItem(i)->getName() << "  |\n";
            cout << "\t";
            repeatText("=", nameLen + 6, false);
        }
        else
        {
            if (activeItem == i - 1)
                cout << endl;

            cout << "\t  " << menu->getItem(i)->getName() << endl;
        }
    }
    cout << endl;
}

void TestApp::showResult(const char *result)
{
    if (result != nullptr && strlen(result) > 0)
        cout << "\n\n\t" << result << "\n\n";
    cout << "\tPress any key to continue...\n";
    Menu::getKey();
}

void TestApp::repeatText(const char *text, size_t count, bool isEndl)
{
    for (size_t i = 0; i < count; i++)
        cout << text;

    if (isEndl)
        cout << endl;
}

void TestApp::outAsciiData(const size_t length, const Byte *buffer)
{
    for (size_t i = 0; i < length; i++)
    {
        if (isprint(buffer[i]))
            cout << buffer[i];
        else
            cout << '.';
    }

}

void TestApp::outRawData(const Reg16Addr startAddr, const size_t length, const Byte *buffer)
{
    for (size_t i = 0; i < length; i++)
    {
        if (i % 16 == 0)
            cout << endl << "0x" << hex << uppercase << setfill('0') << setw(4) << startAddr + i << ":\t";
        cout << hex << uppercase << setfill('0') << setw(2) << (int)buffer[i] << ' ';
    }
}

Reg16Addr TestApp::inputAddress(const bool showDefault, const Reg16Addr defaultAddr)
{
    size_t count = 0;

    if (showDefault)
    {
        cout << "0x" << hex << uppercase << setfill('0') << setw(4) << defaultAddr;
        count = 4;
    }

    Reg16Addr result = defaultAddr;

    auto shift = [](const size_t count) -> Byte {return 4 * (4 - count);};

    while(1)
    {
        int keyCode = Menu::getKey();
        char hexDigit = (char)toupper(keyCode);
        if (keyCode == 13 || keyCode == 10)
        {
            if (count)
            {
                cout << endl;
                break;
            }
        }
        else if (keyCode == 127)
        {
            if (count)
            {
                cout << '\b' << ' ' << '\b';
                count--;
                result = (result >> shift(count)) << shift(count);
            }
        }
        else if (count < 4 && isxdigit(hexDigit))
        {
            cout << hexDigit;
            count++;
            Reg16Value hexValue = hexDigit <= '9' ? hexDigit - '0' : hexDigit - 'A' + 10;
            result |= (hexValue << shift(count));
        }
    }

    //cout << endl << "result: 0x" << hex << uppercase << setfill('0') << setw(4) << result;

    return result;
}

//-----------------------------------------------------------------------

void TestApp::initPeriphery()
{
    PeripheryAccess::initGpio();
    PeripheryAccess::setGpioMode(LED1_GPIO_PIN, GpioMode::OUTPUT);
    PeripheryAccess::setGpioMode(LED2_GPIO_PIN, GpioMode::OUTPUT);
    PeripheryAccess::setGpioMode(BUZZER_GPIO_PIN, GpioMode::OUTPUT);
    PeripheryAccess::setGpioValue(LED1_GPIO_PIN, LOW);
    PeripheryAccess::setGpioValue(LED2_GPIO_PIN, LOW);
    PeripheryAccess::setGpioValue(BUZZER_GPIO_PIN, LOW);

    rtc.initialize(I2C1);
}

void TestApp::activateLeds1(bool isActive)
{
    PeripheryAccess::setGpioValue(LED1_GPIO_PIN, isActive);
}

void TestApp::activateLeds2(bool isActive)
{
    PeripheryAccess::setGpioValue(LED2_GPIO_PIN, isActive);
}

void TestApp::activateBuzzer(bool isActive)
{
    PeripheryAccess::setGpioValue(BUZZER_GPIO_PIN, isActive);
}

void TestApp::doCycles(Byte pin1, size_t numCycles, Byte pin2, size_t usHighTime, size_t usLowTime)
{
    bool isPinHigh = false;

    PeripheryAccess::setGpioValue(pin1, LOW);
    if (pin2 != 255)
        PeripheryAccess::setGpioValue(pin2, LOW);

    for (size_t i = 0; i < numCycles; i ++)
    {
        PeripheryAccess::setGpioValue(pin1, !isPinHigh);
        if (pin2 != 255)
            PeripheryAccess::setGpioValue(pin2, isPinHigh);
        isPinHigh = !isPinHigh;
        usleep(usHighTime);

        PeripheryAccess::setGpioValue(pin1, !isPinHigh);
        if (pin2 != 255)
            PeripheryAccess::setGpioValue(pin2, isPinHigh);
        isPinHigh = !isPinHigh;
        usleep(usLowTime);
    }

    PeripheryAccess::setGpioValue(pin1, LOW);
    if (pin2 != 255)
        PeripheryAccess::setGpioValue(pin2, LOW);
}

void TestApp::outCurrentRtcDateTime()
{
    rtc.initialize(I2C1);
    auto formatedOut = [](int value){ cout << dec << setfill('0') << setw(2) << value; };
    cout << "\n\t----------- READ FROM RTC ------------\n";
    cout << "\tDATE: 20"; formatedOut(rtc.getYear());
    cout << "-"; formatedOut(rtc.getMonth());
    cout << "-"; formatedOut(rtc.getDayOfMonth());
    cout << "\n\tTIME: "; formatedOut(rtc.getHours());
    cout << ":"; formatedOut(rtc.getMinutes());
    cout << ":"; formatedOut(rtc.getSeconds());
    cout << "\n\t--------------------------------------\n";
}

void TestApp::setRtcFromLocalDateTime()
{
    rtc.initialize(I2C1);
    time_t now = time(0);
    struct tm dateTime = *localtime(&now);

    rtc.setDate(dateTime.tm_year, dateTime.tm_mon + 1, dateTime.tm_mday);
    rtc.setTime(dateTime.tm_hour, dateTime.tm_min, dateTime.tm_sec);
}

void TestApp::readEEPROM(const bool isAscii)
{
    PeripheryInitResult initResult = PeripheryAccess::initI2C(I2C0, 0x57);
    cout << "\n\t------------ READ EEPROM -------------\n";
    if (initResult == SUCCESS || initResult == ALREADY_INITIALIZED)
    {
        Reg16Value length = 20;
        cout << "\tPlease input 16-bit addres of EEPROM to read: ";
        Reg16Addr addr = inputAddress(true);
        cout << "\tPlease input length of data to read: ";
        cin >> length;
        length = length == 0 ? 20 : length;
        Byte buffer[21] = {0};
        cout << "\n\tPlease wait... Reading data is in progress...\n";

        I2cAccessResult result = PeripheryAccess::i2cReadBytes16(addr, length, buffer);

        if (result < 0)
        {
            cout << "\n\tRead ERROR!!! Error code: " << dec << result << endl;
        }
        else
        {
            cout << "\n\tSUCCESS! READED DATA:\n\n====== BEGIN OF DATA AREA ======\n";
            if (isAscii)
                outAsciiData(length, buffer);
            else
                outRawData(addr, length, buffer);
            cout << "\n\n====== END OF DATA AREA ======\n";
        }
    }
    else
    {
        cout << "\n\tI2C init ERROR!!! Error code: " << dec << initResult << endl;
    }
    cout << "\n\t--------------------------------------\n";
    Menu::getKey();

}

void TestApp::writeEEPROM()
{
    cout << "\n\t------------ WRITE EEPROM ------------\n";
    PeripheryInitResult initResult = PeripheryAccess::initI2C(I2C0, 0x57);
    if (initResult == SUCCESS || initResult == ALREADY_INITIALIZED)
    {
        string strBuffer = "";
        cout << "\tPlease input 16-bit addres of EEPROM to write: ";
        Reg16Addr addr = inputAddress(true);
        cout << "\n\tPlease input a string data to write: ";
        getline(cin, strBuffer);

        size_t length = strBuffer.length();

        I2cAccessResult result = PeripheryAccess::i2cWriteBytes16(addr, length, (Byte*)(strBuffer.c_str()));
        if (result < 0)
        {
            cout << "\n\tWrite ERROR!!! Error code: " << dec << result << endl;
        }
        else
        {
            cout << "\n\tSUCCESS! " << dec << length << " bytes has been writed!";
        }
    }
    else
    {
        cout << "\n\tI2C init ERROR!!! Error code: " << dec << initResult << endl;
    }

    cout << "\n\t--------------------------------------\n";
}
