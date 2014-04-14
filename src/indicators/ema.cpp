#include "ema.hpp"
#include <iostream>
#include <cmath>

EMA::EMA(int candlesPerPeriod, TimePeriods period)
	: Indicator(candlesPerPeriod, period)
{ }

void EMA::tick(unsigned int time, float price)
{
	currentPrice = price;

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

float EMA::index() 
{
	//expand or contract based on volatility
	const float MAX_DIFFERENCE_THRESHOLD = 40;

	float priceDifference = ema - currentPrice;

	priceDifference = priceDifference > MAX_DIFFERENCE_THRESHOLD 
		? MAX_DIFFERENCE_THRESHOLD 
		: priceDifference;
	priceDifference = priceDifference < -MAX_DIFFERENCE_THRESHOLD
		? -MAX_DIFFERENCE_THRESHOLD
		: priceDifference;

	float index = priceDifference / MAX_DIFFERENCE_THRESHOLD;
	int sign = index > 0 ? 1 : -1;
	index = pow(index, 2) * sign;

	return index;
}