# 1. Basic

```sh
❯ py segmentation.py -c -s1
ARG seed 1
ARG address space size 1k
ARG phys mem size 16k

Segment register information:

  Segment 0 base  (grows positive) : 0x000030e1 (decimal 12513)
  Segment 0 limit                  : 290

  Segment 1 base  (grows negative) : 0x0000122b (decimal 4651)
  Segment 1 limit                  : 472

Virtual Address Trace
  VA  0: 0x000001fb (decimal:  507) --> SEGMENTATION VIOLATION (SEG0)
  VA  1: 0x000001cc (decimal:  460) --> SEGMENTATION VIOLATION (SEG0)
  VA  2: 0x0000029b (decimal:  667) --> VALID in SEG1: 0x000010c6 (decimal: 4294)
  VA  3: 0x00000327 (decimal:  807) --> VALID in SEG1: 0x00001152 (decimal: 4434)
  VA  4: 0x00000060 (decimal:   96) --> VALID in SEG0: 0x00003141 (decimal: 12609)

❯ py segmentation.py -c -s2
ARG seed 2
ARG address space size 1k
ARG phys mem size 16k

Segment register information:

  Segment 0 base  (grows positive) : 0x0000039e (decimal 926)
  Segment 0 limit                  : 500

  Segment 1 base  (grows negative) : 0x0000376a (decimal 14186)
  Segment 1 limit                  : 498

Virtual Address Trace
  VA  0: 0x000002f1 (decimal:  753) --> VALID in SEG1: 0x0000365b (decimal: 13915)
  VA  1: 0x000002ad (decimal:  685) --> VALID in SEG1: 0x00003617 (decimal: 13847)
  VA  2: 0x0000013b (decimal:  315) --> VALID in SEG0: 0x000004d9 (decimal: 1241)
  VA  3: 0x0000026c (decimal:  620) --> VALID in SEG1: 0x000035d6 (decimal: 13782)
  VA  4: 0x0000026d (decimal:  621) --> VALID in SEG1: 0x000035d7 (decimal: 13783)

❯ py segmentation.py -c -s3
ARG seed 3
ARG address space size 1k
ARG phys mem size 16k

Segment register information:

  Segment 0 base  (grows positive) : 0x000017ad (decimal 6061)
  Segment 0 limit                  : 316

  Segment 1 base  (grows negative) : 0x00002831 (decimal 10289)
  Segment 1 limit                  : 395

Virtual Address Trace
  VA  0: 0x00000280 (decimal:  640) --> VALID in SEG1: 0x000026b1 (decimal: 9905)
  VA  1: 0x00000043 (decimal:   67) --> VALID in SEG0: 0x000017f0 (decimal: 6128)
  VA  2: 0x0000000d (decimal:   13) --> VALID in SEG0: 0x000017ba (decimal: 6074)
  VA  3: 0x00000359 (decimal:  857) --> VALID in SEG1: 0x0000278a (decimal: 10122)
  VA  4: 0x00000109 (decimal:  265) --> VALID in SEG0: 0x000018b6 (decimal: 6326)
```

```

```

You see address space 1k = 1024= 2^10. 10 is number of bits we need check when translate decimal each VA to binary.

e.g. 640 = 1010000000 having top bit is 1, which means it belongs to segment 1
Or we can think this way: we have 2 segments: seg1: 0-511; seg: 512-1023

Reverse grow mean check if it is in bound [1k-x, 1k] with x is segment's limit

# 2.

The highest legal virtual address in segment 0: 19

The lowest legal virtual address in segment 1: 128 - 20 = 108

Segment 0 physical addresses: 0-19

Segment 1 physical addresses: 492-511

The lowest illegal physical address: 20

The highest illegal physical address: 491

We use option `-A 19,108,20,107`

# 4.

-l = 0.9 \* -a

# 5.

-l 0 -L 0
