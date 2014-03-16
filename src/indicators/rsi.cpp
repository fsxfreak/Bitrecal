#include "rsi.hpp"
#include <iostream>

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
//                std::cout << "\t\t\t\t\t\tdifference:" << difference << std::endl;
        float gain = difference > 0 ? difference : 0;
//                std::cout << "\t\t\t\t\tgain:" << gain << std::endl;
        float loss = difference < 0 ? -difference : 0;
//                std::cout << "\t\t\t\tloss: " << loss << std::endl;

        float avgGain = ((lastAvgGain * (candlesPerPeriod - 1.f)) + gain) 
                                    / candlesPerPeriod;
//                std::cout << "\t\t\tavgGain:" << avgGain << std::endl;
        float avgLoss = ((lastAvgLoss * (candlesPerPeriod - 1.f)) + loss) 
                                    / candlesPerPeriod;
//                std::cout << "\t\tavgLoss:" << avgLoss << std::endl;

        lastPrice = price;
        lastAvgGain = avgGain;
        lastAvgLoss = avgLoss;

        float RS = avgGain / avgLoss;
//                std::cout << "\tRS:" << RS << std::endl;
        rsi = 100.f - (100.f / (1.f + RS));
//                std::cout << "RSI:" << rsi << std::endl;

    }
}

float RSI::get() { return rsi; }