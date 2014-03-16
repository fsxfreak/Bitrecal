#ifndef EMA_HPP
#define EMA_HPP

#include "indicator.hpp"

class EMA : public Indicator
{
public:
	EMA(int candlesPerPeriod, TimePeriods period);

	virtual void tick(unsigned int time, float price);
	virtual float get();
private:
	float ema;
	float lastEma;
};

#endif