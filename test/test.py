import subprocess
import random
from sys import argv

# this script is for automatic tests

def make_input(filename):
    procnum = random.randrange(15, 30)
    f = open(filename, "w")

    def writernd(a, b):
        for i in range(0, procnum):
            f.write(str(
                random.randrange(a, b)
            ) + " ")
        f.write("\n")

    # arrivals
    writernd(0, procnum + 1 // 2)
    # durations
    writernd(3, 30)
    # priorities
    writernd(0, 10)
    # starving time quant
    f.write(str(random.randrange(3, 15)) + "\n")
    # round robin time quant
    f.write(str(random.randrange(3, 15)) + "\n")
    f.close()
    

if __name__ == "__main__":
    if len(argv) != 4:
        print("Arguments:\n - path to the program\n - number of separate runs\n - path to the directory to output to\n")
        exit(1)

    program = argv[1]
    n = int(argv[2])
    outdir = argv[3]
    # check if theres a '/' at the end of the path
    if not outdir.endswith("/"):
        outdir = outdir + "/"
    
    for i in range(0, n):
        infile = outdir + "input_" + str(i + 1)
        outfile = outdir + "output_" + str(i + 1)

        make_input(infile)
        a = ["./" + program, infile, "-af", outfile]
        print(a)
        subprocess.run(a)
