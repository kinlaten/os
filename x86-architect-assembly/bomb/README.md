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
