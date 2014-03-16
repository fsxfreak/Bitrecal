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
    int transactionIndex;
    std::vector<Transaction>* const transactions;

    EMA ema;
    RSI rsi;

    float lastRSI;
};
#endif  //NDEBUG

#endif  //TRADE_BOT_HPP