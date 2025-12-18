#!/usr/bin/env python3

import argparse
import platform
import shutil
import subprocess

import matplotlib.pyplot as plt
import numpy as np

# Argv list
parser = argparse.ArgumentParser()
parser.add_argument("pages", type=int, help="# of bit for page e.g. input 4, page: 1 to 2^3")
parser.add_argument("trials")
parser.add_argument("--single_cpu", action="store_true") # set to True by default
args = parser.parse_args()

# MacOs (Darwin) doesnt support taskset or easy CPU
if platform.system() == "Darwin":
    args.single_cpu = False

data = []

# Create page array [0, 1, 2,...., pages-1]
x = np.arange(args.pages) 

# Convert exponents to powers of 2: [1, 2, 4, 8, 16, ...]
pages = 2**x

for i in pages:
    if args.single_cpu:
        if shutil.which("taskset"): # get path to the command e.g. /home/linuxbrew/.linuxbrew/bin/taskset
            r = subprocess.run(
                ["taskset", "-c", "0", "./tlb.out", str(i), args.trials], #force the program run only on CPU #0
                capture_output=True,
                check=True,
                text=True,
            )
        elif shutil.which("hwloc-bind"):
            r = subprocess.run(
                [
                    "hwloc-bind",
                    "package:0.pu:0",
                    "--",
                    "./tlb.out",
                    str(i),
                    args.trials,
                ],
                capture_output=True,
                check=True,
                text=True,
            )
        else:
            raise Exception("Can't find hwloc-bind or taskset")
    else:
        r = subprocess.run(
            ["./tlb.out", str(i), args.trials],
            capture_output=True,
            check=True,
            text=True,
        )
    data.append(float(r.stdout)) # add process access time of each entry to array

plt.plot(x, data, marker="o", color="orange")
plt.margins(0)
plt.xticks(x, pages, fontsize="x-small")  # evenly spaced
plt.xlabel("Number Of Pages")
plt.ylabel("Time Per Access (ns)")
title = "TLB Size Measurement: "
title += f"{platform.system()} {platform.release()} {platform.machine()}"
if args.single_cpu:
    title += " single CPU"
plt.title(title)
plt.savefig(
    f'{platform.system()}_{args.trials}{"_single.png" if args.single_cpu else ".png"}', dpi=227
)
plt.show()  
