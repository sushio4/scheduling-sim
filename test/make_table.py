import re

for i in range(1, 21):
    fname = "output_" + str(i)
    file = open(fname, "r")
    lines = file.readlines()
    index = lines.index("Waiting times for all algorithms:\n")
    fcfs = 0
    rr = 0
    p = 0
    for j in range(1, 4):
        ln = lines[index + j]
        num = int(re.search("\d+", ln).group(0))

        if ln.find("Priority") != -1:
            p = num
        if ln.find("Round-Robin") != -1:
            rr = num
        if ln.find("FCFS") != -1:
            fcfs = num
    
    print(i, " & ", fcfs, " & ", rr, " & ", p, " \\\\\n\\hline")