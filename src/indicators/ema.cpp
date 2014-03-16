#include "ema.hpp"
#include <iostream>

EMA::EMA(int candlesPerPeriod, TimePeriods period)
	: Indicator(candlesPerPeriod, period)
{ }

void EMA::tick(unsigned int time, float price)
{
	if (time > nextCandleTime)
	{
		nextCandleTime = calculateNextCandleTime(nextCandleTime, period);

		//not enough candles to start yet
		if (prices.size() < candlesPerPeriod)
		{
			prices.push_back(price);
			ema = lastEma = 0;
			return;
		}

		const float k = 2.f / (static_cast<float>(candlesPerPeriod) + 1.f);

		//now we have enough information to begin EMA
		if (!isStarted && prices.size() == candlesPerPeriod)
		{
			float SMA = 0;
			auto it = prices.begin();
			for (; it != prices.end(); ++it)
			{
				SMA += (*it);
			}
			SMA /= candlesPerPeriod;

			ema = (price - SMA) * k + SMA;

			isStarted = true;
			prices.clear();

			return;
		}

		lastEma = ema;
		ema = (price - lastEma) * k + lastEma;
	}
}

float EMA::get() { return ema; }