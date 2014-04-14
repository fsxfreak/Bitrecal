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
    , ema(22, TimePeriods::FOUR_HOUR)
    , rsi(14, TimePeriods::FOUR_HOUR)
    , waitingToBuy(true)
    , waitingToSell(true)
    , fiat(1000.0f)
{
}

void TradeBotTest::tick()
{
    int time =    (*transactions)[transactionIndex].time;
    float price = (*transactions)[transactionIndex].price;
    transactionIndex++;

    ema.tick(time, price);
    rsi.tick(time, price);

    //index = (ema.index() * 2 + rsi.index() / 2);
    index = rsi.index();
    if (transactionIndex <= 1)
        lastIndex = index;

    index = index > NUM_INDICATORS ? 2.0f : index;
    index = index < -NUM_INDICATORS ? -2.0f : index;

    float rsiVal = rsi.get();
    if (time > 1388880000 && rsiVal != lastRSI)
    {
        /*std::cout << "RSI: " << rsiVal
                  << "\tEMA: " << ema.get()
                  << "\tPrice: " << price
                  << "\tTime: " << time
                  << "\tIndex: " << index
                  << std::endl;*/
        decide();   
    }
    lastRSI = rsiVal;

    lastIndex = index;

    if (coin < 0.001)
        coin = 0;
    if (fiat < 0.001)
        fiat = 0;

}

void TradeBotTest::decide()
{
    if (index > 0.7f * NUM_INDICATORS)
    {
        if (fiat > 0)
        {
            if (changeInIndex() >= 0)
            {
                waitingToBuy = true;
                std::cout << "HOLD! " << index << std::endl;
            }
            else if (waitingToBuy && changeInIndex() < 0)
                waitingToBuy = false;
            
            if (!waitingToBuy)
            {
                buy((index / 3) * fiat);
                std::cout << "Bought: " << buy((index / 3) * fiat)
                  << "\tFiat: " << fiat
                  << "\tCoin: " << coin
                  << "\tIndex: " << index
                  << "\tPrice: " << (*transactions)[transactionIndex].price
                  << std::endl;
            }
        }
            
        
    }
    else if (index < -0.7f * NUM_INDICATORS)
    {
        if (coin > 0)
        {
            if (changeInIndex() <= 0)
            {
                waitingToSell = true;
                std::cout << "HOLD! " << index << std::endl;
            }
                
            else if (waitingToSell && changeInIndex() > 0)
                waitingToSell = false;

            if (!waitingToSell)
            {
                sell((-index / 3) * coin);
                std::cout << "Sold: " << sell((-index / 3) * coin)
                      << "\tFiat: " << fiat
                      << "\tCoin: " << coin
                      << "\tIndex: " << index
                      << "\tPrice: " << (*transactions)[transactionIndex].price
                      << std::endl;
            }
        }
            
            
        
    }
}

float TradeBotTest::changeInIndex() { return index - lastIndex; }

float TradeBotTest::buy(float fiats)
{
    //need to keep track of buys to set up appropriate stop losses
    //identify down trends and dont buy in them

    float price = (*transactions)[transactionIndex].price;
    float coins = fiats / price;
    coins *= 0.998;

    coin += coins;
    fiat -= fiats;

    return coins;
}

float TradeBotTest::sell(float coins)
{
    //identify up trends and dont sell in them

    float price = (*transactions)[transactionIndex].price;
    float fiats = coins * price;
    fiats *= 0.998;

    fiat += fiats;
    coin -= coins;

    return fiats;
}
#endif