#include <iostream>
#include <vector>
#include <string>
#include "../include/csv.h"
#include "tradebot.hpp"

struct Transaction;

int main(int argc, char *argv[])
{
#ifdef NDEBUG //NDEBUG means we are using a live bot
    //prepare for real exchange

    TradeBot realBot = TradeBot();
#else //else, we wish to test
    std::vector<Transaction> transactions;
    
    std::cout << "testing" << std::endl;
    
    io::CSVReader<3> in(".btceUSD.csv");
    in.read_header(io::ignore_no_column, "time", "price", "volume");
    
    unsigned int time; 
    float price; 
    float volume;

    while(in.read_row(time, price, volume)) 
    {
        Transaction transaction = { time, price, volume };
        transactions.push_back(transaction);
    }

    TradeBotTest testBot = TradeBotTest(&transactions);
#endif
    
    bool running = true;
    while (running)
    {
#ifdef NDEBUG
        realBot.tick();
#else
        testBot.tick();
#endif
    }
}