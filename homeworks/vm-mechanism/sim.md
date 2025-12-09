# 2.

limit= 930

# 3.

Max base can be 16KB
In this case, with limit 100, maxBase = 16KB-100= 16*1024*1024 - 100 = 16284

# 4.

❯ py relocation.py -s1 -a16m -p100m -l100000000 -c

ARG seed 1
ARG address space size 16m
ARG phys mem size 100m

Base-and-Bounds register information:

Base : 0x002d5b20 (decimal 2972448)
Limit : 100000000

Virtual Address Trace
VA 0: 0x00d5f4b3 (decimal: 14021811) --> VALID: 0x01034fd3 (decimal: 16994259)
VA 1: 0x006ec9d2 (decimal: 7260626) --> VALID: 0x009c24f2 (decimal: 10233074)
VA 2: 0x00c324c9 (decimal: 12788937) --> VALID: 0x00f07fe9 (decimal: 15761385)
VA 3: 0x00008a05 (decimal: 35333) --> VALID: 0x002de525 (decimal: 3007781)
VA 4: 0x007204e5 (decimal: 7472357) --> VALID: 0x009f6005 (decimal: 10444805)
