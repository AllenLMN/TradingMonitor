#ifndef ORDER_H_
#define ORDER_H_

#include "define.h"
#include "order_side.h"
#include "order_action.h"
#include "order_status.h"
#include "offset.h"

#include <stdio.h>
#include <sys/time.h>
#include <fstream>

struct Order {
  timeval shot_time;
  timeval send_time;
  char contract[MAX_CONTRACT_LENGTH];
  double price;
  int size;
  int traded_size;
  OrderSide::Enum side;
  char order_ref[MAX_ORDERREF_SIZE];
  OrderAction::Enum action;
  OrderStatus::Enum status;
  Offset::Enum offset;
  char tbd[128];

  Order()
    : size(0),
      traded_size(0) {
    snprintf(tbd, sizeof(tbd), "%s", "null");
  }

  bool Valid() {
    if (status == OrderStatus::SubmitNew || status == OrderStatus::New) {
      return true;
    }
    return false;
  }
  void Show(std::ofstream &stream) const {
    stream.write((char*)this, sizeof(*this));
  }

  void ShowCsv(FILE* stream) const {
    char shot_time_s[32];
    snprintf(shot_time_s, sizeof(shot_time_s), "%ld.%ld", shot_time.tv_sec, shot_time.tv_usec);
    double shot_time_sec = atof(shot_time_s);
    char send_time_s[32];
    snprintf(send_time_s, sizeof(send_time_s), "%ld.%ld", send_time.tv_sec, send_time.tv_usec);
    double send_time_sec = atof(send_time_s);
    fprintf(stream, "%lf,%lf,%s,%lf,%d,%d,%s,%s,%s,%s,%s,%s\n",shot_time_sec,send_time_sec,contract,price,size,traded_size,OrderSide::ToString(side),order_ref,OrderAction::ToString(action),OrderStatus::ToString(status),Offset::ToString(offset),tbd);
  }

  void Show(FILE* stream) const {
    // timeval show_time;
    // gettimeofday(&show_time, NULL);
    fprintf(stream, "%ld %04ld %ld %04ld Order %s |",
            send_time.tv_sec, send_time.tv_usec, shot_time.tv_sec, shot_time.tv_usec, contract);

      fprintf(stream, " %lf@%d %d %s %s %s %s %s %s\n", price, size, traded_size, OrderSide::ToString(side), order_ref, OrderAction::ToString(action), OrderStatus::ToString(status), Offset::ToString(offset), tbd);
  }
};

#endif  //  ORDER_H_
