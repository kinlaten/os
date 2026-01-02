# Phase 1

```sh
gdb ./bomb
>gdb break phase_1
>gdb run
#Enter random input to fail it
>gdb disassemble # Show Phase1 assembly

Breakpoint 1, 0x0000000000400ee0 in phase_1 ()
(gdb) disassemble
Dump of assembler code for function phase_1:.
0x0000000000400ee0 <+0>: sub $0x8,%rsp
0x0000000000400ee4 <+4>: mov $0x402400,%esi
0x0000000000400ee9 <+9>: call 0x401338 <strings_not_equal>
0x0000000000400eee <+14>: test %eax,%eax
0x0000000000400ef0 <+16>: je 0x400ef7 <phase_1+23>
0x0000000000400ef2 <+18>: call 0x40143a <explode_bomb>
0x0000000000400ef7 <+23>: add $0x8,%rsp
0x0000000000400efb <+27>: ret
End of assembler dump.
```

We can think it as follow:
Line

1. Reserve 8Byte to stack
2. Move $0x402400 to reg $esi
3. Call func <strings_not_equal>: with $esi is second arg for the func, on the other hand, the first arg is $edi but we dont see it defined around here

> GoodRead: [See positional argument registers](https://cs61.seas.harvard.edu/site/2022/Asm/#gsc.tab=0)

-> $0x402400 might save secret key

$eax is register storing return value of function. It is tested is != 0(Success, a&a=a), then jump to mem 0x400ef7. Else bomb!

We do some investigation:

```sh
(gdb) p/x $eax
$2 = 0x603780

(gdb) x/s 0x603780
0x603780 <input_strings>:       "k"  # Not quite

(gdb) x/s 0x402400
0x402400:       "Border relations with Canada have never been better." # Secret Key
```

Also double check why `strings` command

```sh
$ strings bomb | grep Border
Border relations with Canada have never been better.
```

# Phase 2

```sh
(gdb) disassemble phase_2
Dump of assembler code for function phase_2:
   0x0000000000400efc <+0>:     push   %rbp
   0x0000000000400efd <+1>:     push   %rbx
   0x0000000000400efe <+2>:     sub    $0x28,%rsp
   0x0000000000400f02 <+6>:     mov    %rsp,%rsi
   0x0000000000400f05 <+9>:     call   0x40145c <read_six_numbers>
   0x0000000000400f0a <+14>:    cmpl   $0x1,(%rsp)
   0x0000000000400f0e <+18>:    je     0x400f30 <phase_2+52>
   0x0000000000400f10 <+20>:    call   0x40143a <explode_bomb>
   0x0000000000400f15 <+25>:    jmp    0x400f30 <phase_2+52>
   0x0000000000400f17 <+27>:    mov    -0x4(%rbx),%eax
   0x0000000000400f1a <+30>:    add    %eax,%eax
   0x0000000000400f1c <+32>:    cmp    %eax,(%rbx)
   0x0000000000400f1e <+34>:    je     0x400f25 <phase_2+41>
   0x0000000000400f20 <+36>:    call   0x40143a <explode_bomb>
   0x0000000000400f25 <+41>:    add    $0x4,%rbx
   0x0000000000400f29 <+45>:    cmp    %rbp,%rbx
   0x0000000000400f2c <+48>:    jne    0x400f17 <phase_2+27>
   0x0000000000400f2e <+50>:    jmp    0x400f3c <phase_2+64>
   0x0000000000400f30 <+52>:    lea    0x4(%rsp),%rbx
   0x0000000000400f35 <+57>:    lea    0x18(%rsp),%rbp
   0x0000000000400f3a <+62>:    jmp    0x400f17 <phase_2+27>
   0x0000000000400f3c <+64>:    add    $0x28,%rsp
   0x0000000000400f40 <+68>:    pop    %rbx
   0x0000000000400f41 <+69>:    pop    %rbp
   0x0000000000400f42 <+70>:    ret
End of assembler dump.

```

```sh
cmpl   $0x1,(%rsp)
je     0x400f30 <phase_2+52>
call   0x40143a <explode_bomb>
```

If %rsp != 1 then bomb explode! This imply first element should be 1. Else jump to next line

```sh
lea    0x4(%rsp),%rbx
lea    0x18(%rsp),%rbp
```

Each int is 4 bytes, array run from from byte 0 to 24(0x18), second int set to rbx and last byte is set to %rbp. This might use %rbx as iterator and %rbp as terminator

Next, do unconditional jump

```sh
0x0000000000400f3a <+62>: jmp 0x400f17 <phase_2+27>
```

Now we see because we set tbx to second int of array so want to get first int by -4 to it. Then \*2 and compare to next int. If =, jump to line make rbx increase to next int

```sh
0x0000000000400f17 <+27>: mov -0x4(%rbx),%eax
0x0000000000400f1a <+30>: add %eax,%eax
0x0000000000400f1c <+32>: cmp %eax,(%rbx)
0x0000000000400f1e <+34>: je 0x400f25 <phase_2+41>
```

Now we can guess this array is 1 2 4 8 16 32(double linear)

> Tip: We can use [ASM to C converter](https://www.codeconvert.ai/assembly-to-c-converter?id=1d8ed192-eea8-440e-b263-641619cb5aa2)for easy analysis

# Phase 3

```sh
Dump of assembler code for function phase_3:
=> 0x0000000000400f43 <+0>:     sub    $0x18,%rsp
   0x0000000000400f47 <+4>:     lea    0xc(%rsp),%rcx
   0x0000000000400f4c <+9>:     lea    0x8(%rsp),%rdx
   0x0000000000400f51 <+14>:    mov    $0x4025cf,%esi
   0x0000000000400f56 <+19>:    mov    $0x0,%eax
   0x0000000000400f5b <+24>:    call   0x400bf0 <__isoc99_sscanf@plt>
   0x0000000000400f60 <+29>:    cmp    $0x1,%eax
   0x0000000000400f63 <+32>:    jg     0x400f6a <phase_3+39>
   0x0000000000400f65 <+34>:    call   0x40143a <explode_bomb>
   0x0000000000400f6a <+39>:    cmpl   $0x7,0x8(%rsp)
   0x0000000000400f6f <+44>:    ja     0x400fad <phase_3+106>
   0x0000000000400f71 <+46>:    mov    0x8(%rsp),%eax
   0x0000000000400f75 <+50>:    jmp    *0x402470(,%rax,8)
   0x0000000000400f7c <+57>:    mov    $0xcf,%eax
   0x0000000000400f81 <+62>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f83 <+64>:    mov    $0x2c3,%eax
   0x0000000000400f88 <+69>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f8a <+71>:    mov    $0x100,%eax
   0x0000000000400f8f <+76>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f91 <+78>:    mov    $0x185,%eax
   0x0000000000400f96 <+83>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f98 <+85>:    mov    $0xce,%eax
   0x0000000000400f9d <+90>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f9f <+92>:    mov    $0x2aa,%eax
   0x0000000000400fa4 <+97>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400fa6 <+99>:    mov    $0x147,%eax
   0x0000000000400fab <+104>:   jmp    0x400fbe <phase_3+123>
   0x0000000000400fad <+106>:   call   0x40143a <explode_bomb>
   0x0000000000400fb2 <+111>:   mov    $0x0,%eax
   0x0000000000400fb7 <+116>:   jmp    0x400fbe <phase_3+123>
   0x0000000000400fb9 <+118>:   mov    $0x137,%eax
   0x0000000000400fbe <+123>:   cmp    0xc(%rsp),%eax
   0x0000000000400fc2 <+127>:   je     0x400fc9 <phase_3+134>
   0x0000000000400fc4 <+129>:   call   0x40143a <explode_bomb>
   0x0000000000400fc9 <+134>:   add    $0x18,%rsp
   0x0000000000400fcd <+138>:   ret
End of assembler dump.
```

We know that %esi is second arg that is used in next func. So %esi might contains answer

```sh
0x0000000000400f51 <+14>: mov $0x4025cf,%esi
0x0000000000400f56 <+19>: mov $0x0,%eax
0x0000000000400f5b <+24>: call 0x400bf0 <__isoc99_sscanf@plt> #sscanf used to print something

(gdb) x/s 0x4025cf
0x4025cf:       "%d %d"  # At least the format :))
```

This func needs 2 inputs: might be %rdx (%rsp+8) and %rcx (%rsp+12). Also because it check if # inputs <= 1, bomb

```sh
   0x0000000000400f60 <+29>:    cmp    $0x1,%eax
   0x0000000000400f63 <+32>:    jg     0x400f6a <phase_3+39>
   0x0000000000400f65 <+34>:    call   0x40143a <explode_bomb>
```

Next, it check if %rdx < 7, pass bomb line if true

```sh
   0x0000000000400f6a <+39>:    cmpl   $0x7,0x8(%rsp)
   0x0000000000400f6f <+44>:    ja     0x400fad <phase_3+106> # bomb
```

Next, compare %rdx with %eax, then use jump table to choose which case (typical C switch), each table index takes 8 bytes in 64-bit system

```sh
   0x0000000000400f71 <+46>:    mov    0x8(%rsp),%eax
   0x0000000000400f75 <+50>:    jmp    *0x402470(,%rax,8)
```

We can see 8 cases here. Case 7 is after default case(bomb) is because the program is optimized so they are reordered.

```sh
   0x0000000000400f7c <+57>:    mov    $0xcf,%eax
   0x0000000000400f81 <+62>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f83 <+64>:    mov    $0x2c3,%eax
   0x0000000000400f88 <+69>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f8a <+71>:    mov    $0x100,%eax
   0x0000000000400f8f <+76>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f91 <+78>:    mov    $0x185,%eax
   0x0000000000400f96 <+83>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f98 <+85>:    mov    $0xce,%eax
   0x0000000000400f9d <+90>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f9f <+92>:    mov    $0x2aa,%eax
   0x0000000000400fa4 <+97>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400fa6 <+99>:    mov    $0x147,%eax
   0x0000000000400fab <+104>:   jmp    0x400fbe <phase_3+123>
   0x0000000000400fad <+106>:   call   0x40143a <explode_bomb>
   0x0000000000400fb2 <+111>:   mov    $0x0,%eax
   0x0000000000400fb7 <+116>:   jmp    0x400fbe <phase_3+123>
   0x0000000000400fb9 <+118>:   mov    $0x137,%eax
```

Switch case set %eax to a value then compare %rcx to it, if =, is true; else bomb explode

```sh
   0x0000000000400fbe <+123>:   cmp    0xc(%rsp),%eax
```

-> This means: %rdx is whichever value that set %eax = %rcx

Order of case might be random, not exacly linear , we need to use command `nexti` to jump through to see which first arg e.g. %rdx=1 return which line of %eax (in this case it jump to line `0x137, %eax`) -> pair value is (1, 311)

# Phase 4

```
000000000040100c <phase_4>:
  40100c:	48 83 ec 18          	sub    $0x18,%rsp
  401010:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  401015:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  40101a:	be cf 25 40 00       	mov    $0x4025cf,%esi
  40101f:	b8 00 00 00 00       	mov    $0x0,%eax
  401024:	e8 c7 fb ff ff       	call   400bf0 <__isoc99_sscanf@plt>
  401029:	83 f8 02             	cmp    $0x2,%eax
  40102c:	75 07                	jne    401035 <phase_4+0x29>
  40102e:	83 7c 24 08 0e       	cmpl   $0xe,0x8(%rsp)
  401033:	76 05                	jbe    40103a <phase_4+0x2e>
  401035:	e8 00 04 00 00       	call   40143a <explode_bomb>
  40103a:	ba 0e 00 00 00       	mov    $0xe,%edx
  40103f:	be 00 00 00 00       	mov    $0x0,%esi
  401044:	8b 7c 24 08          	mov    0x8(%rsp),%edi
  401048:	e8 81 ff ff ff       	call   400fce <func4>
  40104d:	85 c0                	test   %eax,%eax
  40104f:	75 07                	jne    401058 <phase_4+0x4c>
  401051:	83 7c 24 0c 00       	cmpl   $0x0,0xc(%rsp)
  401056:	74 05                	je     40105d <phase_4+0x51>
  401058:	e8 dd 03 00 00       	call   40143a <explode_bomb>
  40105d:	48 83 c4 18          	add    $0x18,%rsp
  401061:	c3                   	ret

0000000000400fce <func4>:
  400fce:	48 83 ec 08          	sub    $0x8,%rsp
  400fd2:	89 d0                	mov    %edx,%eax
  400fd4:	29 f0                	sub    %esi,%eax
  400fd6:	89 c1                	mov    %eax,%ecx
  400fd8:	c1 e9 1f             	shr    $0x1f,%ecx
  400fdb:	01 c8                	add    %ecx,%eax
  400fdd:	d1 f8                	sar    $1,%eax
  400fdf:	8d 0c 30             	lea    (%rax,%rsi,1),%ecx
  400fe2:	39 f9                	cmp    %edi,%ecx
  400fe4:	7e 0c                	jle    400ff2 <func4+0x24>
  400fe6:	8d 51 ff             	lea    -0x1(%rcx),%edx
  400fe9:	e8 e0 ff ff ff       	call   400fce <func4>
  400fee:	01 c0                	add    %eax,%eax
  400ff0:	eb 15                	jmp    401007 <func4+0x39>
  400ff2:	b8 00 00 00 00       	mov    $0x0,%eax
  400ff7:	39 f9                	cmp    %edi,%ecx
  400ff9:	7d 0c                	jge    401007 <func4+0x39>
  400ffb:	8d 71 01             	lea    0x1(%rcx),%esi
  400ffe:	e8 cb ff ff ff       	call   400fce <func4>
  401003:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  401007:	48 83 c4 08          	add    $0x8,%rsp
  40100b:	c3                   	ret
```

Extract info from mem slot `0x4025cf` we have format of result is "%d %d"

Convert phase_4 and func4 to C code as follow:

```c
#include <stdio.h>
#include <stdlib.h>

void explode_bomb();

int func4(int val, int low, int high);

void phase_4(char *input) {
    int numbers[2];
    int result;

    // sscanf(input, "%d %d", &numbers[0], &numbers[1]);
    if (sscanf(input, "%d %d", &numbers[0], &numbers[1]) != 2) {
        explode_bomb();
    }

    if (numbers[0] > 14) {
        explode_bomb();
    }

    result = func4(numbers[0], 0, 14);

    if (result != numbers[1]) {
        explode_bomb();
    }
}

int func4(int a, int low, int high) {
  int result = high - low;
  int sign = result >> 31;
  result = (result + sign) >> 1;
  int mid = result + low;

  if (mid > a) {
    // Target is in the lower half
    return 2 * func4(a, low, mid - 1);
  } else if (mid < a) {
    // Target is in the upper half
    return 2 * func4(a, mid + 1, high) + 1;
  } else {
    // Found it!
    return 0;
  }
}
```

func4 take 3 args so that means %edi,%esi(=0),%edx(=14) are used.

So we add main() to test what value return from func4 at root (first try): we have 0, 1, 3, 7 for %rdi which return %eax=0

# Phase 5

```c
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

extern int string_length(const char *str);
extern void explode_bomb(void);
extern int strings_not_equal(const char *s1, const char *s2);

void phase_5(const char *input) {
    // Simulate stack canary check
    uintptr_t canary = *(uintptr_t *)((char *)&canary - sizeof(uintptr_t)); // placeholder for fs:0x28
    uintptr_t canary_check = canary;

    int len = string_length(input);
    if (len != 6) {
        explode_bomb();
    }

    unsigned char mapped[7] = {0}; // 6 chars + null terminator
    static const unsigned char lookup_table[16] = {
        // This corresponds to the data at 0x4024b0 in assembly
        // Since we don't have the exact values, we assume it's a 16-byte lookup table.
        // You need to fill this with the actual values from the binary.
        0x??, 0x??, 0x??, 0x??, 0x??, 0x??, 0x??, 0x??,
        0x??, 0x??, 0x??, 0x??, 0x??, 0x??, 0x??, 0x??
    };

    for (int i = 0; i < 6; i++) {
        unsigned char c = (unsigned char)input[i];
        unsigned char index = c & 0xf;
        mapped[i] = lookup_table[index];
    }
    mapped[6] = '\0';

    static const char *target = (const char *)0x40245e; // address of target string in assembly
    // You need to replace this with the actual target string from the binary.
    // For example:
    // static const char *target = "target_string";

    if (strings_not_equal(mapped, target)) {
        explode_bomb();
    }

    if (canary != canary_check) {
        // stack smashing detected
        __stack_chk_fail();
    }
}
```

Translate assembly to C as above we see 0x4024b0 might be start address of lookup_table: `maduiersnfotvbyl`

```sh
(gdb) x/s 0x4024b0
0x4024b0 <array.3449>:  "maduiersnfotvbylSo you think you can stop the bomb with ctrl-c, do you?"
```

As loop run 6 times, this means secret string should be 6 chars

```sh
(gdb) x/s $rbx
0x6038c0 <input_strings+320>:   "flyers"
```

So that mean we need to find secret key that are translated into `flyers`

By try all alphabets, each try with 6 chars e.g. abcdef, ghijkl ... . And use command

```sh
(gdb) until *0x00000000004010bd  #=> 0x00000000004010bd <+91>:    call   0x401338 <strings_not_equal>
(gdb) x/s $rdi # return translated string
```

Thus we create this lookup_table

```txt
a=a
b=d
c=u
d=i
e=e 4
f=r 5
g=s 6
h=n
i=f 1
j=o
k=t
l=v
m=b
n=y 3
o=l 2
p=m
q=a
r=d
s=u
t=i
u=e 4
v=r 5
w=s 6
x=n
y=f 1
z=o
```

-> secret key is: `yonuvw`

# Phase 6

Code in C as follow:

```c
struct Node {
    int value;     // Offset 0x0
    int id;        // Offset 0x4
    struct Node* next; // Offset 0x8
};

void phase_6(char* input_str) {
    int nums[6];           // Space reserved by: sub $0x50, %rsp
    struct Node* nodes[6]; // Space starting at: 0x20(%rsp)

    /* --- STEP 0: Input --- */
    // 401103: mov %rsp, %rsi
    // 401106: call 40145c <read_six_numbers>
    read_six_numbers(input_str, nums);

    /* --- STEP 1: Validation Loop (Uniqueness & Range) --- */
    // 40110e: mov $0x0, %r12d (i = 0)
    for (int i = 0; i < 6; i++) {
        // 401117: mov 0x0(%r13), %eax
        // 40111b: sub $0x1, %eax
        // 40111e: cmp $0x5, %eax
        if ((unsigned int)(nums[i] - 1) > 5) { // 401121: jbe (jump if below or equal)
            explode_bomb(); // 401123: call explode_bomb
        }

        // 401128: add $0x1, %r12d
        // 401132: mov %r12d, %ebx (j = i + 1)
        for (int j = i + 1; j < 6; j++) {
            // 401138: mov (%rsp,%rax,4), %eax
            // 40113b: cmp %eax, 0x0(%rbp)
            if (nums[i] == nums[j]) {
                explode_bomb(); // 401140: call explode_bomb
            }
            // 401145: add $0x1, %ebx
        }
        // 40114d: add $0x4, %r13 (Move to next input number)
    }

    /* --- STEP 2: Transformation (7 - x) --- */
    // 40115b: mov $0x7, %ecx
    for (int i = 0; i < 6; i++) {
        // 401162: sub (%rax), %edx (edx = 7 - nums[i])
        // 401164: mov %edx, (%rax) (nums[i] = edx)
        nums[i] = 7 - nums[i];
        // 401166: add $0x4, %rax
    }

    /* --- STEP 3: Linked List Mapping --- */
    // This loop populates a list of pointers at 0x20(%rsp)
    // 40116f: mov $0x0, %esi (index = 0)
    for (int i = 0; i < 6; i++) {
        // 401197: mov (%rsp,%rsi,1), %ecx (get nums[i])
        struct Node* curr = (struct Node*)0x6032d0; // 401183: mov $0x6032d0, %edx

        // 401176: mov 0x8(%rdx), %rdx (Walk the list)
        for (int j = 1; j < nums[i]; j++) {
            curr = curr->next;
        }
        // 401188: mov %rdx, 0x20(%rsp,%rsi,2) (Save node pointer to stack)
        nodes[i] = curr;
    }

    /* --- STEP 4: Relinking the List --- */
    // 4011ab: mov 0x20(%rsp), %rbx (Get first node pointer)
    struct Node* head = nodes[0];
    struct Node* temp = head;
    for (int i = 1; i < 6; i++) {
        // 4011bd: mov (%rax), %rdx
        // 4011c0: mov %rdx, 0x8(%rcx) (Set current->next = next_node)
        temp->next = nodes[i];
        temp = nodes[i];
    }
    // 4011d2: movq $0x0, 0x8(%rdx) (Last node -> next = NULL)
    temp->next = NULL;

    /* --- STEP 5: Final Descending Check --- */
    // 4011da: mov $0x5, %ebp (Loop 5 times for 6 nodes)
    struct Node* curr = head;
    while (ebp != 0) {
        // 4011df: mov 0x8(%rbx), %rax
        // 4011e3: mov (%rax), %eax (get value of next node)
        // 4011e5: cmp %eax, (%rbx) (compare current->value with next->value)
        if (curr->value < curr->next->value) { // 4011e7: jge (jump if greater/equal)
            explode_bomb(); // 4011e9: call explode_bomb
        }
        curr = curr->next; // 4011ee: mov 0x8(%rbx), %rbx
        // 4011f2: sub $0x1, %ebp
    }
}
```

So we know that input is:

- 6 ints
- each int of functions read_six_numbers return is between 1 and 6
- No 2 ints are same
  -> numbers\[6\]={1, 2, 3, 4, 5, 6} elements can in any order

See each node take 4B int, 4B id, 8B pointer -> total 16 Bytes -> 2 giant words (each giantword is 8B)

```sh
(gdb) x/12gx 0x6032d0
0x6032d0 <node1>:       0x000000010000014c      0x00000000006032e0
0x6032e0 <node2>:       0x00000002000000a8      0x00000000006032f0
0x6032f0 <node3>:       0x000000030000039c      0x0000000000603300
0x603300 <node4>:       0x00000004000002b3      0x0000000000603310
0x603310 <node5>:       0x00000005000001dd      0x0000000000603320
0x603320 <node6>:       0x00000006000001bb      0x0000000000000000
```

`value` is int, so it take first lower 4Bytes

```txt
node1 0x14c (322)
node2 0xa8 (168)
node3 0x39c (924)
node4 0x2b3 (691)
node5 0x1dd (477)
node6 0x1bb (443)
```

So we order these node in descending order as `3 4 5 6 1 2` -> input numbers

Put them through transformation `7-numbers[i]`: secret key is `4 3 2 1 6 5`
