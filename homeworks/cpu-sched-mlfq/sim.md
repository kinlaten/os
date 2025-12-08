# 1.

## `py mlfq.py -q 5 -a 1 -j 2 -m 10 -c`

Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 3
OPTIONS allotments for queue 2 is 1
OPTIONS quantum length for queue 2 is 5
OPTIONS allotments for queue 1 is 1
OPTIONS quantum length for queue 1 is 5
OPTIONS allotments for queue 0 is 1
OPTIONS quantum length for queue 0 is 5
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False

For each job, three defining characteristics are given:
startTime : at what time does the job enter the system
runTime : the total CPU time needed by the job to finish
ioFreq : every ioFreq time units, the job issues an I/O
(the I/O takes ioTime units to complete)

Job List:
Job 0: startTime 0 - runTime 8 - ioFreq 7
Job 1: startTime 0 - runTime 4 - ioFreq 3

Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 7 (of 8) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 6 (of 8) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 5 (of 8) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 4 (of 8) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 3 (of 8) ]
[ time 5 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 3 (of 4) ]
[ time 6 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 2 (of 4) ]
[ time 7 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 1 (of 4) ]
[ time 8 ] IO_START by JOB 1
IO DONE
[ time 8 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 2 (of 8) ]
[ time 9 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 1 (of 8) ]
[ time 10 ] IO_START by JOB 0
IO DONE
[ time 10 ] IDLE
[ time 11 ] IDLE
[ time 12 ] IDLE
[ time 13 ] IO_DONE by JOB 1
[ time 13 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 0 (of 4) ]
[ time 14 ] FINISHED JOB 1
[ time 14 ] IDLE
[ time 15 ] IO_DONE by JOB 0
[ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 0 (of 8) ]
[ time 16 ] FINISHED JOB 0

Final statistics:
Job 0: startTime 0 - response 0 - turnaround 16
Job 1: startTime 0 - response 5 - turnaround 14

Avg 1: startTime n/a - response 2.50 - turnaround 15.00

## py mlfq.py -q 5 -a 1 -j 2 -m 20 -s 1 -c

Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 3
OPTIONS allotments for queue 2 is 1
OPTIONS quantum length for queue 2 is 5
OPTIONS allotments for queue 1 is 1
OPTIONS quantum length for queue 1 is 5
OPTIONS allotments for queue 0 is 1
OPTIONS quantum length for queue 0 is 5
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False

For each job, three defining characteristics are given:
startTime : at what time does the job enter the system
runTime : the total CPU time needed by the job to finish
ioFreq : every ioFreq time units, the job issues an I/O
(the I/O takes ioTime units to complete)

Job List:
Job 0: startTime 0 - runTime 3 - ioFreq 8
Job 1: startTime 0 - runTime 15 - ioFreq 3

Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 2 (of 3) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 1 (of 3) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 0 (of 3) ]
[ time 3 ] FINISHED JOB 0
[ time 3 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 14 (of 15) ]
[ time 4 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 13 (of 15) ]
[ time 5 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 12 (of 15) ]
[ time 6 ] IO_START by JOB 1
IO DONE
[ time 6 ] IDLE
[ time 7 ] IDLE
[ time 8 ] IDLE
[ time 9 ] IDLE
[ time 10 ] IDLE
[ time 11 ] IO_DONE by JOB 1
[ time 11 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 11 (of 15) ]
[ time 12 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 10 (of 15) ]
[ time 13 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 9 (of 15) ]
[ time 14 ] IO_START by JOB 1
IO DONE
[ time 14 ] IDLE
[ time 15 ] IDLE
[ time 16 ] IDLE
[ time 17 ] IDLE
[ time 18 ] IDLE
[ time 19 ] IO_DONE by JOB 1
[ time 19 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 8 (of 15) ]
[ time 20 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 7 (of 15) ]
[ time 21 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 6 (of 15) ]
[ time 22 ] IO_START by JOB 1
IO DONE
[ time 22 ] IDLE
[ time 23 ] IDLE
[ time 24 ] IDLE
[ time 25 ] IDLE
[ time 26 ] IDLE
[ time 27 ] IO_DONE by JOB 1
[ time 27 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 5 (of 15) ]
[ time 28 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 15) ]
[ time 29 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 15) ]
[ time 30 ] IO_START by JOB 1
IO DONE
[ time 30 ] IDLE
[ time 31 ] IDLE
[ time 32 ] IDLE
[ time 33 ] IDLE
[ time 34 ] IDLE
[ time 35 ] IO_DONE by JOB 1
[ time 35 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 15) ]
[ time 36 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 15) ]
[ time 37 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 15) ]
[ time 38 ] FINISHED JOB 1

Final statistics:
Job 0: startTime 0 - response 0 - turnaround 3
Job 1: startTime 0 - response 3 - turnaround 38

Avg 1: startTime n/a - response 1.50 - turnaround 20.50

# 2.

// Figure 8.2 Long-running Job Over Time
$ ./mlfq.py -n 3 -q 10 -l 0,200,0 -c

// Figure 8.3 Along Came An Interactive Job
$ ./mlfq.py -n 3 -q 10 -l 0,180,0:100,20,0 -c

// Figure 8.4 A Mixed I/O-intensive and CPU-intensive Workload
$ ./mlfq.py -n 3 -q 10 -l 0,175,0:50,25,1 -i 5 -S -c

// Figure 8.5 without priority boost
$ ./mlfq.py -n 3 -q 10 -l 0,120,0:100,50,1:100,50,1 -i 1 -S -c

// Figure 8.5 with priority boost
$ ./mlfq.py -n 3 -q 10 -l 0,120,0:100,50,1:100,50,1 -i 1 -S -B 50 -c

// Figure 8.6 without gaming tolerance
$ ./mlfq.py -n 3 -q 10 -i 1 -S -l 0,200,0:80,100,9 -c

// Figure 8.6 with gaming tolerance
$ ./mlfq.py -n 3 -q 10 -i 1 -l 0,200,0:80,100,9 -c

// Figure 8.7 Lower Priority, Longer Quanta
$ ./mlfq.py -n 3 -a 2 -Q 10,20,40 -l 0,200,0:0,200,0 -c

# 3. How would you configure the scheduler parameters to behave just like a round-robin scheduler?

time slice <= (max job length / jobs number)

# 4. Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.

$ ./mlfq.py -n 3 -q 10 -l 0,50,0:0,50,9 -i 1 -S -c

# 5. Given a system with a quantum length of 10ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long-running (and potentially-starving) job gets at least 5% of the CPU?

200ms

$ ./mlfq.py -n 3 -q 10 -l 0,200,0:0,200,1:0,200,1 -i 1 -S -B 200 -c

# 6.One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.

$ ./mlfq.py -n 2 -q 10 -l 0,50,0:0,50,11 -i 1 -S -c
$ ./mlfq.py -n 2 -q 10 -l 0,50,0:0,50,11 -i 1 -S -I -c
