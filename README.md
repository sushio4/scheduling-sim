# Scheduling algorithm simulator
## Overview
It is a simple program to simulate and display information about certain task scheduling algorithms. 
Currently available ones:
- FCFS (FIFO)
- Round-robin
- Priority pre-emptive

## Usage
schedule [options] [input file]

Available options:
 - -h shows this message
 - -f [FILE] stores info in a FILE
 - -v shows every step, enter vv for graphical represenation
 - -a selects all algorithms and compares them

Algorithms:
 - -R corresponds to Round-robin algorithm
 - -F corresponds to FCFS algorithm
 - -P corresponds to Priority Pre-empting algorithm

Examples:

`./schedule input.txt -af output.txt`
* Compares all algorithms and stores the result in the file output.txt

`./schedule -Rvv input.txt`
* Runs Round-robin algorithm, prints step by step info and displays graphical representation of a process queue

`./schedule -h`
* Displays help message

## Input file format
Numbers in a line shall be delimited by spaces

The following lines are required:
1. Arrival times
2. Duration times
3. Priorities
4. Time quant for starvation (1 number)
5. Time quant for RR

Example input file (input.txt):
```
0 0 1 1 1 1 2 3 4 4 4 4 5 6 6
27 22 3 12 25 21 13 23 17 19 27 11 18 3 14
6 4 9 3 3 8 8 5 1 0 1 7 4 4 1
3
5

```
## Test script
`test/test.py` script automatically makes a bunch of random inputs, runs the simulation with `-af` flags and stores them in output files
### Usage
It takes 3 arguments:
1. Path to program
2. Number of tests
3. Directory for output

Example:
`python3 test.py ../build/schedule 3 .`

Will result in such files (assuming we're in `test` directory)
```
build
    schedule
    (...)
test
    test.py
    input_1
    input_2
    input_3
    output_1
    output_2
    output_3
(...)
```
