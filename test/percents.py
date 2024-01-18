import re

fcfs = 0
rr = 0
p = 0

for i in range(1, 21):
    fname = "output_" + str(i)
    file = open(fname, "r")
    lines = file.readlines()
    index = lines.index("Waiting times for all algorithms:\n")
    ln = lines[index + 5]
    if ln.find("Round-Robin") != -1:
        rr = rr + 1
    if ln.find("FCFS") != -1:
        fcfs = fcfs + 1
    if ln.find("Priority") != -1:
        p = p + 1

print("FCFS: " , str(fcfs * 5), "\nRound-Robin: ", str(rr * 5), "\nPriority: ", str(p * 5), '\n')
