#include "tradebot.hpp"

#include <iostream>

#ifdef NDEBUG
TradeBot::TradeBot()
{
    std::cout << "real tick" << std::endl;
}

void TradeBot::tick()
{
    
}

#else
TradeBotTest::TradeBotTest(std::vector<Transaction>* const transactionsOther)
    : transactionIndex(0)
    , transactions(transactionsOther)
    , ema(22, TimePeriods::FIFTEEN_MINUTE)
    , rsi(14, TimePeriods::FIFTEEN_MINUTE)
{
}

void TradeBotTest::tick()
{
    int time =  (*transactions)[transactionIndex].time;
    int price = (*transactions)[transactionIndex].price;
    transactionIndex++;

    ema.tick(time, price);
    rsi.tick(time, price);

    float rsiVal = rsi.get();
    if (time > 1380499200 && lastRSI != rsiVal)
    {
        std::cout << "RSI: " << rsiVal
                  << "\tEMA: " << ema.get()
                  << "\tPrice: " << price
                  << "\tTime: " << time
                  << std::endl;
    }
    lastRSI = rsiVal;

    //make an index based on RSI, EMA, previous highs, previous lows based on time
}
#endif