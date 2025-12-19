# 1.

Just need the top level page directory base register

# 2.

Use example of Virtual Address 0x611c

## Top level: multi-level page table

VPN 10 bit
Offset 5 bit
PFN 7 bit

VA: 11000(24) 01000(8) 11100(28)

PDBR: 108
We have page 108:83fee0da7fd47febbe9ed5ade4ac90d692d8c1f89fe1ede9a1e8c7c2a9d1dbff

## Second level: Page directory

- Byte 0th: 0x83
- Byte 24th(first 5 bit of VPN decides PDE): 0xA1
  = 1(Valid bit) 0100001(PTE = 33 in dec) -> Let see at page 33

Page 33: 7f7f7f7f7f7f7f7fb57f9d7f7f7f7f7f7f7f7f7f7f7f7f7f7f7ff6b17f7f7f7f

## Third Level: Page table

- Byte 0th: 0x7f
- Byte 8th (next 5 bit after first 5 bit of VPN decides offset of the PDE): 0xB5
  = 1(Valid bit) 0110101(PFN)

-> PA: (PFN << SHIFT) OR offset = 0110101 00000 | 11100 = 0110101(53) 11100(28) = 0x6bc

Page 53: 0f0c18090e121c0f081713071c1e191b09161b150e030d121c1d0e1a08181100

- Byte 28th: 0x08 (FINAL VALUE!!)

So totally we use 3 refs: PDE, PTE, and data fetch

# 3.

Every time TLB miss, the top-level table (only 1 itself) is accessed to find to corresponding table (1 of many). Thus, top-level is rarely evicted from cache -> good temporal locality

For second-level table entry: program likely access memory linearly: next segment of page or next page. -> good spatial locality
