# 1.

- Timer `clock_gettime` use struct `timespec` which has resolution of nano seconds
- Timer `getttimeofday` use struct `timeval` which has resolution of micro seconds

# 2, 3.

Read `tlp.c`

If #trial <= #pages, access time is very high.

```sh
❯ ./tlp 9 0
Invalid input
❯ ./tlp 9 1
121.333333
❯ ./tlp 9 9
15.345679
```

When #trial >= #pages \* 10000 (or more), access time is reliable

```sh
❯ ./tlp 9 100
3.194444
❯ ./tlp 9 200
2.632778
❯ ./tlp 9 500
2.306444
❯ ./tlp 9 50
4.297778
❯ ./tlp 9 1000
2.150778
❯ ./tlp 9 10000
1.895556
❯ ./tlp 9 20000
2.283956
#####
❯ ./tlp 9 100000
1.914481
❯ ./tlp 9 100000
1.968871
❯ ./tlp 9 100000
2.022349
❯ ./tlp 9 100000
2.100441
❯ ./tlp 9 100000
1.996491
❯ ./tlp 9 100000
1.932549
```

# 4.

Visualize paging access time `plot.py`

```sh
gcc -o tlp tlb.c
python3 plot.py 14 100000 --single_cpu

# Eyeball is a good medium
```

# 5.

Using gcc's optimize option gcc -O0 to disable optimization. This is the default setting.

-O0 No optimization. Translates code exactly as written.
-O1 Basic optimizations that don't take much time.
-O2 Heavy optimization. High chance of deleting "useless" loops.
-O3 Uses SIMD (vectorization) and loop unrolling.

# 6.

To get good measurement, avoid context-switch:

Use sched_setaffinity(2), pthread_setaffinity_np(3), taskset(1) or `sudo systemd-run -p AllowedCPUs=0 ./tlb.out` on Linux

cpuset_setaffinity(2) or cpuset(1) on FreeBSD.

Or use `hwloc-bind package:0.pu:0 -- ./tlb.out` on MacOs

# 7.

OS promises that mem seg is allocated for using but it is only actually allocated until we start use it. Thus, if many op happen in close time, this very expensive.

So we can use `calloc` to write binary 0 to those segments as a init

# Ref

https://stackoverflow.com/questions/1538420/difference-between-malloc-and-calloc
https://stackoverflow.com/questions/53708076/what-is-the-proper-way-to-use-clock-gettime
https://pyjamabrah.com/posts/do-while-magic/
