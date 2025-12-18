# 1.

- Timer `clock_gettime` use struct `timespec` which has resolution of nano seconds
- Timer `getttimeofday` use struct `timeval` which has resolution of micro seconds

# 2.

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
