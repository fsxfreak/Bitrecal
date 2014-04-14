#include "rsi.hpp"
#include <iostream>
#include <cmath>

//All times in seconds, timeNow is unix time
RSI::RSI(int candlesPerPeriod, TimePeriods period)
    : Indicator(candlesPerPeriod, period)
{ }

void RSI::tick(unsigned int time, float price)
{
    if (time > nextCandleTime) //time to update RSI
    {
        nextCandleTime = calculateNextCandleTime(nextCandleTime, period);

        //not enough candles to begin yet
        if (prices.size() < (candlesPerPeriod + 1)) //+ 1 for RS calculation
        {
            prices.push_back(price);
            rsi = 0;
            return;
        }

        //now we have enough information to begin RSI
        if (!isStarted && prices.size() == (candlesPerPeriod + 1))
        {
            float gains = 0.f;
            float losses = 0.f;

            auto it = prices.begin();
            ++it;
            float lastPrice = (*prices.begin());
            for (; it != prices.end(); ++it)
            {
                float current = (*it);
                if (current - lastPrice > 0)
                    gains += current;
                else
                    losses += current;

                lastPrice = current;
            }

            lastAvgGain = gains /= candlesPerPeriod;
            lastAvgLoss = losses /= candlesPerPeriod;
            float RS = gains / losses;
            rsi = 100.f - (100.f / (1.f + RS));

            lastPrice = (*prices.end());

            isStarted = true;
            prices.clear();

            return;
        }

        float difference = price - lastPrice;
        float gain = difference > 0 ? difference : 0;
        float loss = difference < 0 ? -difference : 0;

        float avgGain = ((lastAvgGain * (candlesPerPeriod - 1.f)) + gain) 
                                    / candlesPerPeriod;
        float avgLoss = ((lastAvgLoss * (candlesPerPeriod - 1.f)) + loss) 
                                    / candlesPerPeriod;

        lastPrice = price;
        lastAvgGain = avgGain;
        lastAvgLoss = avgLoss;

        float RS = avgGain / avgLoss;
        rsi = 100.f - (100.f / (1.f + RS));
    }
}

float RSI::get() { return rsi; }

float RSI::index()
{
    float difference = 50 - rsi;
    float index = difference / 50;
    index = cbrt(index);

    return index;
}