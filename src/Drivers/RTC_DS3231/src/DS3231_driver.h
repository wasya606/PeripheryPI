#ifndef __DS3231_DRIVER_H__VDYKYY
#define __DS3231_DRIVER_H__VDYKYY
#include "rtc_types.h"
#include "peripherial_access.h"
#include "DS3231_hardware.h"

using namespace Rtc;

class RtcDriver
{
public:
    RtcDriver();
    ~RtcDriver();

    /**
     * @brief initialize
     * @param ioDevice - index of i2c master hardware(for RPI3: 0, 1 or 2)
     * @return  if initialized - PeripheryInitResult::SUCCESS and PeripheryInitResult::ERROR_* if init error occurred
     */
    PeripheryInitResult initialize(const I2cDevice device);

    /**
     * @brief start - starts clock
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult start();

    /**
     * @brief stop - stops clock
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult stop();

    /**
     * @brief setDate - sets the current date
     * @param date - Date struct object reference
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setDate(const Date& date);

    /**
     * @brief setYear - sets the current year
     * @param year
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setYear(const Byte year);

    /**
     * @brief setMonth - sets the current month
     * @param month
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setMonth(const Byte month);

    /**
     * @brief setDay - sets the current day
     * @param day
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setDay(const Byte day);

    /**
     * @brief setHours - sets the current hours
     * @param hours
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setHours(const Byte hours);

    /**
     * @brief setMinutes - sets the current minutes
     * @param minutes
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setMinutes(const Byte minutes);

    /**
     * @brief setSeconds - sets the current seconds
     * @param seconds
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setSeconds(const Byte seconds);

    /**
     * @brief setDate - sets the current date
     * @param year - last two digit of year (range: 0 - 99)
     * @param month - number of month in year (range: 1 - 12)
     * @param day - day of month (range: 1 - 31)
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setDate(const Byte year, const Byte month, const Byte day);

    /**
     * @brief setTime - sets current time
     * @param time - Time struct object reference
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setTime(const Time& time);

    /**
     * @brief setTime - sets current time
     * @param hours - range: 0 - 24
     * @param minutes - range: 0 - 60
     * @param seconds - range: 0 - 60
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setTime(const Byte hours, const Byte minutes, const Byte seconds);

    /**
     * @brief setDateTime sets current date and time
     * @param dateTime - a DateTime struct object reference
     * @return I2cAccessResult::I2C_NO_ERRORS if success or I2cAccessResult::ERROR_* if error occurred
     */
    I2cAccessResult setDateTime(const DateTime& dateTime);

    /**
     * @brief getDate
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    Date* getDate() const;

    /**
     * @brief getTime
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    Time* getTime() const;

    /**
     * @brief getDateTime
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    DateTime* getDateTime() const;

    /**
     * @brief getYear
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getYear() const;

    /**
     * @brief getMonth
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getMonth() const;

    /**
     * @brief getDayOfMonth
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getDayOfMonth() const;

    /**
     * @brief getDayOfWeek
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getDayOfWeek() const;

    /**
     * @brief getHours
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getHours() const;

    /**
     * @brief getMinutes
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getMinutes() const;

    /**
     * @brief getSeconds
     * @return ReadValue(int) - if returned value is a positive int then readed_value = returned_value & 0xFF,
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getSeconds() const;

    /**
     * @brief getAmPmFlag
     * @return ReadValue(int) - if returned value is a positive int then readed_value = (HourAmPmFlag)returned_value(0 - AM, 1 - PM),
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getAmPmFlag() const;

    /**
     * @brief getHourFormat
     * @return ReadValue(int) - if returned value is a positive int then readed_value = (HourFormat)returned_value(0 - 24H, 1 - 12H),
     *                          else an error occurred and returned value contains the error code (I2cAccessResult::ERROR_*)
     */
    ReadValue getHourFormat() const;

private:
    static inline ReadValue readRegister(const Reg8Addr regAddr);
    static inline I2cAccessResult writeRegister(const Reg8Value data, const Reg8Addr regAddr);
    static inline Reg8Value getValue(const ReadValue readValue);

private:
    Date* currentDate;
    Time* currentTime;
    DateTime* currentDateTime;



};

#endif // __DS3231_DRIVER_H__VDYKYY
