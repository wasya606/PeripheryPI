#ifndef __RTC_TYPES_H__VDYKYY
#define __RTC_TYPES_H__VDYKYY
#include "peripherial_types.h"

using namespace PeripheralTypes;

namespace Rtc {

enum HourFormat { H24 = 0, H12 = 1 };
enum HourAmPmFlag { AM = 0, PM = 1 };

struct Date
{
    Byte year = 0;
    Byte month = 1;
    Byte dayOfMonth = 1;
    Byte dayOfWeek = 1;
};

struct Time
{
    Byte hours = 0;
    Byte minutes = 0;
    Byte seconds = 0;
    HourFormat hourFormat = H12;
    HourAmPmFlag amPm = AM;
};

struct DateTime
{
    Date* date = nullptr;
    Time* time = nullptr;
};

}

#endif // __RTC_TYPES_H__VDYKYY
