#include "indicator.hpp"

constexpr unsigned long long operator"" 
    _mins(unsigned long long minutes) { return minutes * 60; }
constexpr unsigned long long operator"" 
    _hrs(unsigned long long hours) { return hours * 60_mins; }
constexpr unsigned long long operator"" 
    _days(unsigned long long days) { return days * 24_hrs;   }

unsigned int calculateNextCandleTime(unsigned int timeNow, TimePeriods period)
{
    switch(period)
    {
    case MINUTE:
        return timeNow + 1_mins;
    case FIVE_MINUTE:
        return timeNow + 5_mins;
    case FIFTEEN_MINUTE:
        return timeNow + 15_mins;
    case THIRTY_MINUTE:
        return timeNow + 30_mins;
    case HOUR:
        return timeNow + 1_hrs;
    case TWO_HOUR:
        return timeNow + 2_hrs;
    case FOUR_HOUR:
        return timeNow + 4_hrs;
    case DAY:
        return timeNow + 1_days;
    case WEEK:
        return timeNow + 7_days;
    }

    return 0;
}

Indicator::Indicator(int candlesPerPeriodOther, TimePeriods periodOther)
    : candlesPerPeriod(candlesPerPeriodOther)
    , period(periodOther)
    , nextCandleTime(0)
{ }
