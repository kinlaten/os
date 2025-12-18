# 1.

Number of page entry = virtual address size / virtual page size
e.g. `-a 1m -P 1k` gives 1023 table entries
`-a 1m -P 2k` gives 511 table entries

# 2.

With `-a 100` means probability page table is allocated 100%

```
Virtual Address Trace
  VA 0x000010ab (decimal:     4267) --> 12ab10ab (decimal 313200811) [VPN 4]
  VA 0x00003385 (decimal:    13189) --> 0338f385 (decimal 54064005) [VPN 12]
  VA 0x0000231d (decimal:     8989) --> 1f72fb1d (decimal 527629085) [VPN 8]
  VA 0x000000e6 (decimal:      230) --> 184128e6 (decimal 406923494) [VPN 0]
  VA 0x00002e0f (decimal:    11791) --> 15e3320f (decimal 367211023) [VPN 11]
```

This is `-a 0`

```
Virtual Address Trace
  VA 0x00003a39 (decimal:    14905) -->  Invalid (VPN 14 not valid)
  VA 0x00003ee5 (decimal:    16101) -->  Invalid (VPN 15 not valid)
  VA 0x000033da (decimal:    13274) -->  Invalid (VPN 12 not valid)
  VA 0x000039bd (decimal:    14781) -->  Invalid (VPN 14 not valid)
  VA 0x000013d9 (decimal:     5081) -->  Invalid (VPN 4 not valid)
```

# 3.

The first is too small and the third is too big

# 4.

```sh
$ ./paging-linear-translate.py -a 65k -v -c
ARG address space size 65k
ARG phys mem size 64k
Error: physical memory size must be GREATER than address space size (for this simulation)

$ ./paging-linear-translate.py -a 0 -v -c
ARG address space size 0
Error: must specify a non-zero address-space size.

$ ./paging-linear-translate.py -p 0 -v -c
ARG phys mem size 0
Error: must specify a non-zero physical memory size.

$ ./paging-linear-translate.py -P 0 -v -c
Traceback (most recent call last):
File "./paging-linear-translate.py", line 85, in <module>
mustbemultipleof(asize, pagesize, 'address space must be a multiple of the pagesize')
File "./paging-linear-translate.py", line 14, in mustbemultipleof
if (int(float(bignum)/float(num)) != (int(bignum) / int(num))):
ZeroDivisionError: float division by zero

$ ./paging-linear-translate.py -P 32k -v -c
Traceback (most recent call last):
File "./paging-linear-translate.py", line 174, in <module>
if pt[vpn] < 0:
IndexError: array index out of range
```
