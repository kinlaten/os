#!/usr/bin/env python3

import random
from operator import itemgetter

random.seed(0)
num_addrs = 10
max_page = 10
count = {}
addr_list = []

while 1:
    # generate randomly element for a list: [0..10]. Also count each of them
    for i in range(num_addrs):
        n = int(max_page * random.random())  # 10 * [0...1]
        addr_list.append(n)

        if n in count:
            count[n] += 1
        else:
            count[n] = 1

    # descending order by second property (count)
    sorted_count = sorted(count.items(), key=itemgetter(1), reverse=True)

    # Temporal Locality
    count_sum = 0
    for k in range(int(0.2 * num_addrs)):  # 20/80 rule: 20% page is hot access
        count_sum += sorted_count[k][1]

    if count_sum / num_addrs >= 0.8:
        break
    else:
        count = {}
        addr_list = []
        # loop repeat

print(addr_list)
