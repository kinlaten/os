# 1.

```sh
❯ ./paging-policy.py -s 0 -n 10 -c
./paging-policy.py -s 0 -n 10 -c --policy=LRU
./paging-policy.py -s 0 -n 10 -c --policy=OPT
ARG addresses -1
ARG addressfile
ARG numaddrs 10
ARG policy FIFO
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 8  MISS FirstIn ->          [8] <- Lastin  Replaced:- [Hits:0 Misses:1]
Access: 7  MISS FirstIn ->       [8, 7] <- Lastin  Replaced:- [Hits:0 Misses:2]
Access: 4  MISS FirstIn ->    [8, 7, 4] <- Lastin  Replaced:- [Hits:0 Misses:3]
Access: 2  MISS FirstIn ->    [7, 4, 2] <- Lastin  Replaced:8 [Hits:0 Misses:4]
Access: 5  MISS FirstIn ->    [4, 2, 5] <- Lastin  Replaced:7 [Hits:0 Misses:5]
Access: 4  HIT  FirstIn ->    [4, 2, 5] <- Lastin  Replaced:- [Hits:1 Misses:5]
Access: 7  MISS FirstIn ->    [2, 5, 7] <- Lastin  Replaced:4 [Hits:1 Misses:6]
Access: 3  MISS FirstIn ->    [5, 7, 3] <- Lastin  Replaced:2 [Hits:1 Misses:7]
Access: 4  MISS FirstIn ->    [7, 3, 4] <- Lastin  Replaced:5 [Hits:1 Misses:8]
Access: 5  MISS FirstIn ->    [3, 4, 5] <- Lastin  Replaced:7 [Hits:1 Misses:9]

#FINALSTATS hits 1   misses 9   hitrate 10.00

ARG addresses -1
ARG addressfile
ARG numaddrs 10
ARG policy LRU
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 8  MISS LRU ->          [8] <- MRU Replaced:- [Hits:0 Misses:1]
Access: 7  MISS LRU ->       [8, 7] <- MRU Replaced:- [Hits:0 Misses:2]
Access: 4  MISS LRU ->    [8, 7, 4] <- MRU Replaced:- [Hits:0 Misses:3]
Access: 2  MISS LRU ->    [7, 4, 2] <- MRU Replaced:8 [Hits:0 Misses:4]
Access: 5  MISS LRU ->    [4, 2, 5] <- MRU Replaced:7 [Hits:0 Misses:5]
Access: 4  HIT  LRU ->    [2, 5, 4] <- MRU Replaced:- [Hits:1 Misses:5]
Access: 7  MISS LRU ->    [5, 4, 7] <- MRU Replaced:2 [Hits:1 Misses:6]
Access: 3  MISS LRU ->    [4, 7, 3] <- MRU Replaced:5 [Hits:1 Misses:7]
Access: 4  HIT  LRU ->    [7, 3, 4] <- MRU Replaced:- [Hits:2 Misses:7]
Access: 5  MISS LRU ->    [3, 4, 5] <- MRU Replaced:7 [Hits:2 Misses:8]

#FINALSTATS hits 2   misses 8   hitrate 20.00

ARG addresses -1
ARG addressfile
ARG numaddrs 10
ARG policy OPT
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 8  MISS Left  ->          [8] <- Right Replaced:- [Hits:0 Misses:1]
Access: 7  MISS Left  ->       [8, 7] <- Right Replaced:- [Hits:0 Misses:2]
Access: 4  MISS Left  ->    [8, 7, 4] <- Right Replaced:- [Hits:0 Misses:3]
Access: 2  MISS Left  ->    [7, 4, 2] <- Right Replaced:8 [Hits:0 Misses:4]
Access: 5  MISS Left  ->    [7, 4, 5] <- Right Replaced:2 [Hits:0 Misses:5]
Access: 4  HIT  Left  ->    [7, 4, 5] <- Right Replaced:- [Hits:1 Misses:5]
Access: 7  HIT  Left  ->    [7, 4, 5] <- Right Replaced:- [Hits:2 Misses:5]
Access: 3  MISS Left  ->    [4, 5, 3] <- Right Replaced:7 [Hits:2 Misses:6]
Access: 4  HIT  Left  ->    [4, 5, 3] <- Right Replaced:- [Hits:3 Misses:6]
Access: 5  HIT  Left  ->    [4, 5, 3] <- Right Replaced:- [Hits:4 Misses:6]

#FINALSTATS hits 4   misses 6   hitrate 40.00
```

# 2.

```sh
./paging-policy.py --addresses=0,1,2,3,4,5,0,1,2,3,4,5 --policy=FIFO --cachesize=5 -c
#

./paging-policy.py --addresses=0,1,2,3,4,5,0,1,2,3,4,5 --policy=LRU --cachesize=5 -c
#

./paging-policy.py --addresses=0,1,2,3,4,5,4,5,4,5,4,5 --policy=MRU --cachesize=5 -c
#
```

All three of them have hit rate 0% haha

# 3.

```sh
./paging-policy.py -s 0 -n 10 -c
#FINALSTATS hits 1   misses 9   hitrate 10.00

./paging-policy.py -s 0 -n 10 -c --policy=LRU
#FINALSTATS hits 2   misses 8   hitrate 20.00

./paging-policy.py -s 0 -n 10 -c --policy=OPT
#FINALSTATS hits 4   misses 6   hitrate 40.00

./paging-policy.py -s 0 -n 10 -c --policy=UNOPT
#FINALSTATS hits 0   misses 10   hitrate 0.00

./paging-policy.py -s 0 -n 10 -c --policy=RAND
#FINALSTATS hits 0   misses 10   hitrate 0.00

./paging-policy.py -s 0 -n 10 -c --policy=CLOCK
#FINALSTATS hits 1   misses 9   hitrate 10.00
```

# 4.

```sh
❯ ./run-trace.sh
--- Policy: LRU ---
ARG addresses 3,0,6,6,6,6,7,0,6,6
ARG addressfile
ARG numaddrs 10
ARG policy LRU
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 3  MISS LRU ->          [3] <- MRU Replaced:- [Hits:0 Misses:1]
Access: 0  MISS LRU ->       [3, 0] <- MRU Replaced:- [Hits:0 Misses:2]
Access: 6  MISS LRU ->    [3, 0, 6] <- MRU Replaced:- [Hits:0 Misses:3]
Access: 6  HIT  LRU ->    [3, 0, 6] <- MRU Replaced:- [Hits:1 Misses:3]
Access: 6  HIT  LRU ->    [3, 0, 6] <- MRU Replaced:- [Hits:2 Misses:3]
Access: 6  HIT  LRU ->    [3, 0, 6] <- MRU Replaced:- [Hits:3 Misses:3]
Access: 7  MISS LRU ->    [0, 6, 7] <- MRU Replaced:3 [Hits:3 Misses:4]
Access: 0  HIT  LRU ->    [6, 7, 0] <- MRU Replaced:- [Hits:4 Misses:4]
Access: 6  HIT  LRU ->    [7, 0, 6] <- MRU Replaced:- [Hits:5 Misses:4]
Access: 6  HIT  LRU ->    [7, 0, 6] <- MRU Replaced:- [Hits:6 Misses:4]

FINALSTATS hits 6   misses 4   hitrate 60.00

--- Policy: RAND ---
ARG addresses 3,0,6,6,6,6,7,0,6,6
ARG addressfile
ARG numaddrs 10
ARG policy RAND
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 3  MISS Left  ->          [3] <- Right Replaced:- [Hits:0 Misses:1]
Access: 0  MISS Left  ->       [3, 0] <- Right Replaced:- [Hits:0 Misses:2]
Access: 6  MISS Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:0 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:1 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:2 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:3 Misses:3]
Access: 7  MISS Left  ->    [3, 0, 7] <- Right Replaced:6 [Hits:3 Misses:4]
Access: 0  HIT  Left  ->    [3, 0, 7] <- Right Replaced:- [Hits:4 Misses:4]
Access: 6  MISS Left  ->    [3, 0, 6] <- Right Replaced:7 [Hits:4 Misses:5]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:5 Misses:5]

FINALSTATS hits 5   misses 5   hitrate 50.00

--- Policy: CLOCK (Bits: 0) ---
ARG addresses 3,0,6,6,6,6,7,0,6,6
ARG addressfile
ARG numaddrs 10
ARG policy CLOCK
ARG clockbits 0
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 3  MISS Left  ->          [3] <- Right Replaced:- [Hits:0 Misses:1]
Access: 0  MISS Left  ->       [3, 0] <- Right Replaced:- [Hits:0 Misses:2]
Access: 6  MISS Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:0 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:1 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:2 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:3 Misses:3]
Access: 7  MISS Left  ->    [3, 0, 7] <- Right Replaced:6 [Hits:3 Misses:4]
Access: 0  HIT  Left  ->    [3, 0, 7] <- Right Replaced:- [Hits:4 Misses:4]
Access: 6  MISS Left  ->    [3, 7, 6] <- Right Replaced:0 [Hits:4 Misses:5]
Access: 6  HIT  Left  ->    [3, 7, 6] <- Right Replaced:- [Hits:5 Misses:5]

FINALSTATS hits 5   misses 5   hitrate 50.00

--- Policy: CLOCK (Bits: 1) ---
ARG addresses 3,0,6,6,6,6,7,0,6,6
ARG addressfile
ARG numaddrs 10
ARG policy CLOCK
ARG clockbits 1
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 3  MISS Left  ->          [3] <- Right Replaced:- [Hits:0 Misses:1]
Access: 0  MISS Left  ->       [3, 0] <- Right Replaced:- [Hits:0 Misses:2]
Access: 6  MISS Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:0 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:1 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:2 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:3 Misses:3]
Access: 7  MISS Left  ->    [3, 0, 7] <- Right Replaced:6 [Hits:3 Misses:4]
Access: 0  HIT  Left  ->    [3, 0, 7] <- Right Replaced:- [Hits:4 Misses:4]
Access: 6  MISS Left  ->    [3, 7, 6] <- Right Replaced:0 [Hits:4 Misses:5]
Access: 6  HIT  Left  ->    [3, 7, 6] <- Right Replaced:- [Hits:5 Misses:5]

FINALSTATS hits 5   misses 5   hitrate 50.00

--- Policy: CLOCK (Bits: 2) ---
ARG addresses 3,0,6,6,6,6,7,0,6,6
ARG addressfile
ARG numaddrs 10
ARG policy CLOCK
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 3  MISS Left  ->          [3] <- Right Replaced:- [Hits:0 Misses:1]
Access: 0  MISS Left  ->       [3, 0] <- Right Replaced:- [Hits:0 Misses:2]
Access: 6  MISS Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:0 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:1 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:2 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:3 Misses:3]
Access: 7  MISS Left  ->    [3, 6, 7] <- Right Replaced:0 [Hits:3 Misses:4]
Access: 0  MISS Left  ->    [3, 7, 0] <- Right Replaced:6 [Hits:3 Misses:5]
Access: 6  MISS Left  ->    [7, 0, 6] <- Right Replaced:3 [Hits:3 Misses:6]
Access: 6  HIT  Left  ->    [7, 0, 6] <- Right Replaced:- [Hits:4 Misses:6]

FINALSTATS hits 4   misses 6   hitrate 40.00

--- Policy: CLOCK (Bits: 3) ---
ARG addresses 3,0,6,6,6,6,7,0,6,6
ARG addressfile
ARG numaddrs 10
ARG policy CLOCK
ARG clockbits 3
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Solving...

Access: 3  MISS Left  ->          [3] <- Right Replaced:- [Hits:0 Misses:1]
Access: 0  MISS Left  ->       [3, 0] <- Right Replaced:- [Hits:0 Misses:2]
Access: 6  MISS Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:0 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:1 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:2 Misses:3]
Access: 6  HIT  Left  ->    [3, 0, 6] <- Right Replaced:- [Hits:3 Misses:3]
Access: 7  MISS Left  ->    [3, 6, 7] <- Right Replaced:0 [Hits:3 Misses:4]
Access: 0  MISS Left  ->    [6, 7, 0] <- Right Replaced:3 [Hits:3 Misses:5]
Access: 6  HIT  Left  ->    [6, 7, 0] <- Right Replaced:- [Hits:4 Misses:5]
Access: 6  HIT  Left  ->    [6, 7, 0] <- Right Replaced:- [Hits:5 Misses:5]

FINALSTATS hits 5   misses 5   hitrate 50.00

~/Doc/g/os/h/vm-beyondphys-policy main !1 ?11 ❯                                                          12:14:55 PM
```

Hit rate with different clock bits doesnt change
