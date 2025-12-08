# 1.

```sh
❯ gcc -o null null.c
❯ ./null
zsh: segmentation fault (core dumped) ./null
```

# 2.

Program received signal SIGSEGV, Segmentation fault.
0x0000555555555161 in main () at null.c:5
5 int result = \*ptr;

# 3.

❯ valgrind --leak-check=yes ./null
==911199== Memcheck, a memory error detector
==911199== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==911199== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==911199== Command: ./null
==911199==
==911199== Invalid read of size 4
==911199== at 0x109161: main (null.c:5)
==911199== Address 0x0 is not stack'd, malloc'd or (recently) free'd
==911199==
==911199==
==911199== Process terminating with default action of signal 11 (SIGSEGV)
==911199== Access not within mapped region at address 0x0
==911199== at 0x109161: main (null.c:5)
==911199== If you believe this happened as a result of a stack
==911199== overflow in your program's main thread (unlikely but
==911199== possible), you can try to increase the size of the
==911199== main thread stack using the --main-stacksize= flag.
==911199== The main thread stack size used in this run was 8388608.
==911199==
==911199== HEAP SUMMARY:
==911199== in use at exit: 0 bytes in 0 blocks
==911199== total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==911199==
==911199== All heap blocks were freed -- no leaks are possible
==911199==
==911199== For lists of detected and suppressed errors, rerun with: -s
==911199== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
zsh: segmentation fault (core dumped) valgrind --leak-check=yes ./null

->Explain:
==911199== HEAP SUMMARY:
==911199== in use at exit: 0 bytes in 0 blocks
==911199== total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==911199== All heap blocks were freed -- no leaks are possible

No leak happen but mem access policy is violated.

# 4.

❯ valgrind --leak-check=yes ./notFree
==933716== Memcheck, a memory error detector
==933716== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==933716== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==933716== Command: ./notFree
==933716==
==933716==
==933716== HEAP SUMMARY:
==933716== in use at exit: 10 bytes in 1 blocks
==933716== total heap usage: 1 allocs, 0 frees, 10 bytes allocated
==933716==
==933716== 10 bytes in 1 blocks are definitely lost in loss record 1 of 1
==933716== at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==933716== by 0x10915E: main (in /home/ed/Documents/gitRepo/os/homeworks/vm-api/notFree)
==933716==
==933716== LEAK SUMMARY:
==933716== definitely lost: 10 bytes in 1 blocks
==933716== indirectly lost: 0 bytes in 0 blocks
==933716== possibly lost: 0 bytes in 0 blocks
==933716== still reachable: 0 bytes in 0 blocks
==933716== suppressed: 0 bytes in 0 blocks
==933716==
==933716== For lists of detected and suppressed errors, rerun with: -s
==933716== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

# 5.

❯ valgrind --leak-check=yes ./array1
==921935== Memcheck, a memory error detector
==921935== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==921935== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==921935== Command: ./array
==921935==
==921935== Invalid write of size 4
==921935== at 0x10918D: main (in /home/ed/Documents/gitRepo/os/homeworks/vm-api/array)
==921935== Address 0x4a901d0 is 0 bytes after a block of size 400 alloc'd
==921935== at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==921935== by 0x10917E: main (in /home/ed/Documents/gitRepo/os/homeworks/vm-api/array)
==921935==
==921935==
==921935== HEAP SUMMARY:
==921935== in use at exit: 0 bytes in 0 blocks
==921935== total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==921935==
==921935== All heap blocks were freed -- no leaks are possible
==921935==
==921935== For lists of detected and suppressed errors, rerun with: -s
==921935== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

# 6.

It returns random values

❯ gcc -o array2 array2.c;./array2
6
❯ gcc -o array2 array2.c;./array2
5

❯ valgrind --leak-check=yes ./array2
==930107== Memcheck, a memory error detector
==930107== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==930107== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==930107== Command: ./array2
==930107==
==930107== Invalid read of size 4
==930107== at 0x1091C5: main (in /home/ed/Documents/gitRepo/os/homeworks/vm-api/array2)
==930107== Address 0x4a90044 is 4 bytes inside a block of size 400 free'd
==930107== at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==930107== by 0x1091BC: main (in /home/ed/Documents/gitRepo/os/homeworks/vm-api/array2)
==930107== Block was alloc'd at
==930107== at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==930107== by 0x10919E: main (in /home/ed/Documents/gitRepo/os/homeworks/vm-api/array2)
==930107==
15
==930107==
==930107== HEAP SUMMARY:
==930107== in use at exit: 0 bytes in 0 blocks
==930107== total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==930107==
==930107== All heap blocks were freed -- no leaks are possible
==930107==
==930107== For lists of detected and suppressed errors, rerun with: -s
==930107== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

# 7.

```sh
❯ gcc -o freeMiddlePointer freeMiddlePointer.c; ./freeMiddlePointer
freeMiddlePointer.c: In function ‘main’:
freeMiddlePointer.c:7:3: warning: ‘free’ called on pointer ‘arr’ with nonzero offset 16 [-Wfree-nonheap-object]
    7 |   free(arr + 4);
      |   ^~~~~~~~~~~~~
freeMiddlePointer.c:5:14: note: returned from ‘malloc’
    5 |   int *arr = malloc(100 * sizeof(int));
      |              ^~~~~~~~~~~~~~~~~~~~~~~~~
Address: 0x6507341312a0
free(): invalid pointer
zsh: IOT instruction (core dumped)  ./freeMiddlePointer
```
