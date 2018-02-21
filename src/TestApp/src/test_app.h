#ifndef __TESTAPP_H__VDYKYY__
#define __TESTAPP_H__VDYKYY__
#include "Menu/menu.h"
#include "test_gpio.h"
#include "peripherial_access.h"
#include "DS3231_driver.h"

class TestApp
{
public:
    TestApp();
    ~TestApp();

    void start();

private:
    void createMenu();
    void mainMenuHandler(MenuItem* item);
    void updateMenu();
    void showResult(const char* result = nullptr);
    void repeatText(const char* text, size_t count, bool isEndl = true);
    void outAsciiData(const size_t length, const Byte* buffer);
    void outRawData(const Reg16Addr startAddr, const size_t length, const Byte* buffer);
    Reg16Addr inputAddress(const bool showDefault, const Reg16Addr defaultAddr = 0x0000);

private:
    Menu* menu;
    RtcDriver rtc;

private:
    void initPeriphery();
    void activateLeds1(bool isActive);
    void activateLeds2(bool isActive);
    void activateBuzzer(bool isActive);
    void doCycles(Byte pin1, size_t numCycles, Byte pin2 = 255, size_t usHighTime = 100000, size_t usLowTime = 100000);
    void setRtcFromLocalDateTime();
    void outCurrentRtcDateTime();
    void readEEPROM(const bool isAscii = true);
    void writeEEPROM();


};

#endif // __TESTAPP_H__VDYKYY__
