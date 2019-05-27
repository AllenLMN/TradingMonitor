A QT-based Trading strategy Frontend UI for hft https://github.com/nickhuangxinyu/hft

open to see the program:
demo/TradingMonitor.exe


pair trading strategy

graph part:
there are six lines in the graph part, they are:
up: up line for open position
down: down line for open
mean: close line
stop_up: stop loss close line for up
stop_down: stop loss close line for down
mid: mid price of A - mid price of B

Strategy logic:
mid > up: open, wait mid back to mean, close, profit is up-mean-fee-cost of execution, if mid do to stopup, close it to stoploss
mid < down: open, wait mid back to mean, close, profit is mean-down-fee-cost of execution, if mid do to stopdown, close it to stoploss

Control Part:
there is a button to let traders to revise those line

Author:
Xinyu Huang
Cindy zhao
