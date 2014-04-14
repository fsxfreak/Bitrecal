#ifndef INDICATOR_HPP
#define INDICATOR_HPP

#include <vector>

//converts all time periods into seconds for comparing with unix time
constexpr unsigned long long operator"" _mins(unsigned long long minutes);
constexpr unsigned long long operator"" _hrs(unsigned long long hours);
constexpr unsigned long long operator"" _days(unsigned long long days);

enum TimePeriods
{
    MINUTE,
        FIVE_MINUTE,
        FIFTEEN_MINUTE,
        THIRTY_MINUTE,
    HOUR,
        TWO_HOUR,
        FOUR_HOUR,
    DAY,
    WEEK
};

unsigned int calculateNextCandleTime(unsigned int timeNow, TimePeriods period);

class Indicator
{
public:
    Indicator(int candlesPerPeriodOther, TimePeriods periodOther); 

    virtual void tick(unsigned int time, float price) = 0;
    virtual float get() = 0;
    virtual float index() = 0;
protected:
    const unsigned int candlesPerPeriod;
    const TimePeriods period;

    unsigned int nextCandleTime;

    //because indicators need previous data to be valid
    std::vector<float> prices;
    bool isStarted; 
};

#endif