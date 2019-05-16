#ifndef MARKET_SNAPSHOT_H_
#define MARKET_SNAPSHOT_H_
#include <QThread>
#include <stdio.h>
//#include <sys/time.h>
// #include "common_tools.h"
#include "define.h"
//#include <winsock.h>
#include <algorithm>
#include <iostream>
#include <fstream>
//#include "timerstruct.h"
//#include <DateTime>
struct timeval2 {
        long  long   tv_sec;         /* seconds */
        long  long  tv_usec;        /* and microseconds */
};
struct MarketSnapshot {
  char ticker[MAX_TICKER_LENGTH];
  double bids[MARKET_DATA_DEPTH];
  double asks[MARKET_DATA_DEPTH];
  int bid_sizes[MARKET_DATA_DEPTH];
  int ask_sizes[MARKET_DATA_DEPTH];
  double last_trade;
  int last_trade_size;
  int volume;
  double turnover;
  double open_interest;
  bool is_trade_update;  // true if updated caused by trade
//  datet time;
timeval2 time;
  bool is_initialized;

  MarketSnapshot()
      : last_trade(0.0),
        last_trade_size(0),
        volume(0),
        turnover(0.0),
        open_interest(0.0),
        is_trade_update(false),
        time(),
        is_initialized(false) {
    ticker[0] = 0;
    for (int i = 0; i < MARKET_DATA_DEPTH; ++i) {
      bids[i] = 0.0;
      asks[i] = 0.0;
      bid_sizes[i] = 0;
      ask_sizes[i] = 0;
    }
  }

  void Show(std::ofstream &stream, int depth = MARKET_DATA_DEPTH) const {
    stream.write((char*)this, sizeof(*this));
  }


  std::string Copy(int depth = MARKET_DATA_DEPTH) {
    std::string s;
    char temp[1024];
//    snprintf(temp, sizeof(temp),  "%ld %04ld SNAPSHOT %s |",
//            time.tv_sec, time.tv_usec, ticker);
    s += temp;

//    int n = std::min(depth, MARKET_DATA_DEPTH);
//    for (int i = 0; i < n; ++i) {
//      snprintf(temp, sizeof(temp), "%s %.12g %.12g | %3d x %3d |", temp,
//              bids[i], asks[i], bid_sizes[i], ask_sizes[i]);
//      s += temp;
//    }

    if (is_trade_update) {
      // T for trade update
      snprintf(temp, sizeof(temp), "%s %.12g %d %d T\n", temp, last_trade, last_trade_size, volume);
    } else {
      // M for market update
      snprintf(temp, sizeof(temp), "%s %.12g %d %d M %.12g %.12g\n", temp, last_trade, last_trade_size, volume, turnover, open_interest);
    }
    s += temp;
    return s;
  }

  bool IsGood() {
    if (bids[0] < 0.001 || asks[0] < 0.001 || ask_sizes[0] <=0 || bid_sizes[0] <= 0) {
      return false;
    }
    return true;
  }
  // checks for invalid / inconsistent sizes, empty market, crossed
  // market, not initialized, or inconsistent market depth
  // check_depth specifies if you care about the consistency in
  // market depth (set to false if you only care about top of book)
  /*
  bool IsGood(bool check_depth = true) const {
    if (bid_sizes[0] <= 0 || ask_sizes[0] <= 0) {
      return false;
    }

    // crossed market
    if (bids[0] - EPS > asks[0]) {
      return false;
    }

    if (!is_initialized) {
      return false;
    }

    // check consistent market depth
    if (check_depth) {
      for (int i = 1; i < MARKET_DATA_DEPTH; ++i) {
        if (bid_sizes[i] > 0 && bids[i] > bids[i-1] - EPS) {
          return false;
        }
        if (ask_sizes[i] > 0 && asks[i] < asks[i-1] + EPS) {
          return false;
        }
      }
    }

    return true;
  }
  */
};

#endif // MARKET_SNAPSHOT_H_
