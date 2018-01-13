#include "DS3231_driver.h"

RtcDriver::RtcDriver() : currentDate(new Date), currentTime(new Time), currentDateTime(new DateTime)
{
}

RtcDriver::~RtcDriver()
{
    if (currentDate != nullptr) delete currentDate;
    if (currentTime != nullptr) delete currentTime;
    if (currentDateTime != nullptr) delete currentDateTime;
}

PeripheryInitResult RtcDriver::initialize(const I2cDevice device)
{
    return PeripheryAccess::initI2C(device, I2C_ADDR);
}

I2cAccessResult RtcDriver::start()
{
    ReadValue readResult = readRegister(CONTROL_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                              writeRegister(getValue(readResult) & (~CONTROL_NOT_EOSCT_MASK), CONTROL_REGISTER);
}

I2cAccessResult RtcDriver::stop()
{
    ReadValue readResult = readRegister(CONTROL_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                              writeRegister(getValue(readResult) | CONTROL_NOT_EOSCT_MASK, CONTROL_REGISTER);
}

I2cAccessResult RtcDriver::setDate(const Date&)
{
    //TODO: NEED TO IMPLEMENT
    return I2C_NO_ERRORS;
}

I2cAccessResult RtcDriver::setYear(const Byte year)
{
    Byte trueYear = year < 100 ? year : year % 100;
    Reg8Value yearValue = (((trueYear / 10) << 4) & YEAR_DOZENS_MASK) | ((trueYear % 10) & YEAR_MASK);
    return writeRegister(yearValue, YEAR_REGISTER);
}

I2cAccessResult RtcDriver::setMonth(const Byte month)
{
    Byte trueMonth = month > 0 ? (month <= 12 ? month : month % 12) : 1;
    Reg8Value monthValue = (((trueMonth / 10) << 4) & MONTH_DOZENS_MASK) | ((trueMonth % 10) & MONTH_MASK);
    return writeRegister(monthValue, MONTH_REGISTER);
}

I2cAccessResult RtcDriver::setDay(const Byte day)
{
    Byte trueDay = day > 0 ? (day <= 31 ? day : day % 31) : 1;
    Reg8Value dayValue = (((trueDay / 10) << 4) & DATE_DAY_DOZENS_MASK) | ((trueDay % 10) & DATE_DAY_MASK);
    return writeRegister(dayValue, DATE_REGISTER);
}

I2cAccessResult RtcDriver::setHours(const Byte hours)
{
    Byte trueHours = hours < 24 ? hours : hours % 24;
    Reg8Value hoursValue = (((trueHours / 20) << 5) & HOURS_TWENTIES_MASK) |
                           (((trueHours / 10) << 4) & HOURS_DOZENS_MASK)   |
                           ((trueHours % 10) & HOURS_MASK);
    return writeRegister(hoursValue, HOURS_REGISTER);

}

I2cAccessResult RtcDriver::setMinutes(const Byte minutes)
{
    Byte trueMinutes = minutes < 60 ? minutes : minutes % 60;
    Reg8Value minutesValue = (((trueMinutes / 10) << 4) & MINUTES_DOZENS_MASK) | ((trueMinutes % 10) & MINUTES_MASK);
    return writeRegister(minutesValue, MINUTES_REGISTER);

}

I2cAccessResult RtcDriver::setSeconds(const Byte seconds)
{
    Byte trueSeconds = seconds < 60 ? seconds : seconds % 60;
    Reg8Value secondsValue = (((trueSeconds / 10) << 4) & SECONDS_DOZENS_MASK) | ((trueSeconds % 10) & SECONDS_MASK);
    return writeRegister(secondsValue, SECONDS_REGISTER);

}

I2cAccessResult RtcDriver::setDate(const Byte year, const Byte month, const Byte day)
{
    I2cAccessResult result = setYear(year);
    if (result == I2C_NO_ERRORS)
    {
        result = setMonth(month);
        if (result == I2C_NO_ERRORS)
            result = setDay(day);
    }
    return result;
}

I2cAccessResult RtcDriver::setTime(const Time&)
{
    //TODO: NEED TO IMPLEMENT
    return I2C_NO_ERRORS;
}

I2cAccessResult RtcDriver::setTime(const Byte hours, const Byte minutes, const Byte seconds)
{
    I2cAccessResult result = setHours(hours);
    if (result == I2C_NO_ERRORS)
    {
        result = setMinutes(minutes);
        if (result == I2C_NO_ERRORS)
            result = setSeconds(seconds);
    }
    return result;
}

I2cAccessResult RtcDriver::setDateTime(const DateTime&)
{
    //TODO: NEED TO IMPLEMENT
    return I2C_NO_ERRORS;
}

Date* RtcDriver::getDate() const
{
    //TODO: NEED TO IMPLEMENT
    return currentDate;
}

Time* RtcDriver::getTime() const
{
    //TODO: NEED TO IMPLEMENT
    return currentTime;
}

DateTime* RtcDriver::getDateTime() const
{
    //TODO: NEED TO IMPLEMENT
    return currentDateTime;
}

ReadValue RtcDriver::getYear() const
{
    ReadValue readResult = readRegister(YEAR_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                              (((getValue(readResult) & YEAR_DOZENS_MASK) >> 4) * 10) +
                              (getValue(readResult) & YEAR_MASK);
}

ReadValue RtcDriver::getMonth() const
{
    ReadValue readResult = readRegister(MONTH_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                              ((getValue(readResult) & MONTH_DOZENS_MASK) >> 4) * 10 +
                               (getValue(readResult) & MONTH_MASK);
}

ReadValue RtcDriver::getDayOfMonth() const
{
    ReadValue readResult = readRegister(DATE_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                              ((getValue(readResult) & DATE_DAY_DOZENS_MASK) >> 4) * 10 +
                               (getValue(readResult) & DATE_DAY_MASK);
}

ReadValue RtcDriver::getDayOfWeek() const
{
    ReadValue readResult = readRegister(DAY_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                               getValue(readResult) & DAY_OF_WEEK_MASK;
}

ReadValue RtcDriver::getHours() const
{
    ReadValue readResult = readRegister(HOURS_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                              (~((getValue(readResult) & HOURS_12_24_MODE_MASK) >> 6) &
                              (((getValue(readResult) & HOURS_TWENTIES_MASK) >> 5) * 20)) +
                               ((getValue(readResult) & HOURS_DOZENS_MASK) >> 4)   * 10 +
                                (getValue(readResult) & HOURS_MASK);
}

ReadValue RtcDriver::getMinutes() const
{
    ReadValue readResult = readRegister(MINUTES_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                              ((getValue(readResult) & MINUTES_DOZENS_MASK) >> 4) * 10 +
                               (getValue(readResult) & MINUTES_MASK);
}

ReadValue RtcDriver::getSeconds() const
{
    ReadValue readResult = readRegister(SECONDS_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult :
                              ((getValue(readResult) & SECONDS_DOZENS_MASK) >> 4) * 10 +
                              (getValue(readResult) & SECONDS_MASK);
}

ReadValue RtcDriver::getAmPmFlag() const
{
    ReadValue readResult = readRegister(HOURS_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult : ((getValue(readResult) & HOURS_AM_PM_FLAG_MASK) >> 5);
}

ReadValue RtcDriver::getHourFormat() const
{
    ReadValue readResult = readRegister(HOURS_REGISTER);
    return (readResult < 0) ? (I2cAccessResult)readResult : ((getValue(readResult) & HOURS_12_24_MODE_MASK) >> 6);
}

ReadValue RtcDriver::readRegister(const Reg8Addr regAddr)
{
    return PeripheryAccess::i2cReadByte(regAddr);
}

I2cAccessResult RtcDriver::writeRegister(const Reg8Value data, const Reg8Addr regAddr)
{
    return PeripheryAccess::i2cWriteByte(data, regAddr);
}

Reg8Value RtcDriver::getValue(const ReadValue readValue)
{
    return readValue & 0xFF;
}

