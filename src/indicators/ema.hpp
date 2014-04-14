#ifndef EMA_HPP
#define EMA_HPP

#include "indicator.hpp"

class EMA : public Indicator
{
public:
	EMA(int candlesPerPeriod, TimePeriods period);

	virtual void tick(unsigned int time, float price);
	virtual float get();
	virtual float index();
private:
	float ema;
	float lastEma;

	float currentPrice;
};

#endif