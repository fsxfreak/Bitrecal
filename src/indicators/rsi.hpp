#ifndef RSI_HPP
#define RSI_HPP

#include "indicator.hpp"

class RSI : public Indicator
{
public:
    RSI(int candlesPerPeriod, TimePeriods period);

    virtual void tick(unsigned int time, float price);
    virtual float get();
private:
    float rsi;

    float lastAvgGain;
    float lastAvgLoss;
    float lastPrice;
};

#endif