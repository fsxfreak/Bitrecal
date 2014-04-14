#ifndef TRADE_BOT_HPP
#define TRADE_BOT_HPP

#include <vector>
#include "indicators/ema.hpp"
#include "indicators/rsi.hpp"

struct Transaction
{
    unsigned int time;
    float price;
    float volume;
};

#ifdef NDEBUG
class TradeBot
{
public:
    TradeBot();
    void tick();

private:

};

#else
class TradeBotTest
{
public:
    TradeBotTest(std::vector<Transaction>* transactionsOther);
    void tick();

private:
    const int NUM_INDICATORS = 1;

    int transactionIndex;
    std::vector<Transaction>* const transactions;

    EMA ema;
    RSI rsi;

    float lastRSI;
    float index;
    float lastIndex;

    bool waitingToBuy;
    bool waitingToSell;

    void decide();
    float changeInIndex();

    float fiat;
    float coin;
    float buy(float amount);
    float sell(float amount);
};
#endif  //NDEBUG

#endif  //TRADE_BOT_HPP