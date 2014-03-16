Bitrecal
========

Bitrecal is a pet project that I created to automate BTC trading while I don't have access to a computer (a majority of my time these days). It relies on technicals to make decisions.

Bitrecal runs in the command line. No user interaction is required after starting the program. All relevant information about indicators, prices, orders, etc. will be displayed using stdout. The use of either the test or live bot depends on a compiler define.

## Exploring

The source for Bitrecal is found under ```src/```.

```./```

* ```tradebot.hpp``` - Contains both TradeBot and TradeBotTest skeletons.
* ```tradebot.cpp``` - Contains the code that decides on orders to place.
* ```main.cpp``` - Initializes either the TradeBot or TradeBotTest, depending on the ```NDEBUG``` #define.


```indicators/```

* ```indicator.hpp``` - Declares an abstract base class that all indicators inherit. Also declares helper functions and the ```TimePeriods``` enum.
* ```indicator.cpp``` - Defines everything declared in ```indicator.hpp```
* ```rsi.hpp``` - Declares the RSI class.
* ```rsi.cpp``` - Defines the RSI class. RSI can be configured to use a specific time interval.
* ```ema.hpp``` - Declares the EMA class.
* ```ema.cpp``` - Defines the EMA class. EMA can be configured to use a specific time interval.

## Dependencies
#### Platform agnostic
* **[BitcoinCharts historical price data](http://api.bitcoincharts.com/v1/csv/)** - Historical Bitcoin prices can be found here.
* **[fast-cpp-csv-parser](https://code.google.com/p/fast-cpp-csv-parser/)** - Used for parsing the historical prices from BitcoinCharts.
* **C++11 features** - If your compiler does not support ```<thread>``` or user-defined literals, you will not be able to compile Bitrecal.

## Usage
#### Downloading
To download, simply
	
	$ git clone https://github.com/fsxfreak/Bitrecal.git

#### Building
**Windows** - Get a fixed version of MinGW for threading from here: [x32-4.8.1-release-posix-sjlj-rev-5.7.z](http://sourceforge.net/projects/mingwbuilds/files/host-windows/releases/4.8.1/32-bit/threads-posix/sjlj/)

The rest should be platform agnostic.
	
	$ cd Bitrecal/src

Testing bot:

	$ g++ -std=gnu++0x main.cpp tradebot.cpp indicators/ema.cpp indicators/rsi.cpp indicators/indicator.cpp -o ../bin/bitrecal.exe -lpthread -Wall

Live bot:

	$ g++ -std=gnu++0x -d NDEBUG main.cpp tradebot.cpp indicators/ema.cpp indicators/rsi.cpp indicators/indicator.cpp -o ../bin/bitrecal.exe -lpthread -Wall

#### Running

    $ cd Bitrecal/bin
    $ bitrecal

If you are running the test bot version, make sure you have the appropriate .csv file from **BitcoinCharts historical price data** above. In order to function with **fast-cpp-csv-parser**, the first line of the .csv file must be as follows:

```time,price,volume```


## Author's comments
In this project, I experimented with C++11 user-defined literals to handle the fact that the times on the historical data was in UNIX time, which is in seconds. I found that using literals to convert units is much more convenient than using traditional functions. 

I also decided to turn on all compiler warnings. Doing so has made me more aware of type strictness, especially in ```const```/```unsigned```/```float```.

Although I am comfortable with my decision to take advantage of inheritance with the Indicators to guarantee that I declare the needed functions, and guarantee that all Indicators structure their information in the same way, I'm unsure as to whether there should be more benefits that I get from doing this. It doesn't make sense to use any polymorphism when running my indicators, as I would lose information about what indicators they actually were, unless I added another bloated enum to my class. So far in my coding experience, object-oriented design has only helped me with organization.

If you use this bot, I am not responsible for any monetary gains or losses you accrue.

## Future plans

In the future, I want to make a learning trade bot that adjusts its own parameters according to fundamentals.

## License

The MIT License (MIT)

Copyright (c) 2014 Leon Cheung

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
