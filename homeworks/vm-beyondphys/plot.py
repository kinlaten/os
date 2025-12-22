#!/usr/bin/env python3

import re
import subprocess
import matplotlib.pyplot as plt
import numpy as np
import time

# 1. Shorten mem arr to first half only ([:3] takes the first 3 items)
mem = [1000, 5000, 10000, 15000, 20000, 25000][:3] 

x = np.array(mem) / 1000
data = []

for i in mem:
    print(f"Testing {i} MB...")
    process = subprocess.Popen(['./mem', str(i)], stdout=subprocess.PIPE, text=True)
    
    vals = []
    start_time = time.time()
    
    while True:
        line = process.stdout.readline()
        
        # 2. Timeout check (10 seconds)
        if (time.time() - start_time) > 10:
            print("  -> Timed out (10s limit reached)")
            process.terminate()
            break
            
        if not line: 
            break # Process ended naturally

        match = re.search(r'bandwidth:\s+([\d.]+)\s+MB/s', line)
        if match:
            vals.append(float(match.group(1)))
            
            # Stop if we have enough samples (e.g. 5) to save time
            if len(vals) >= 5:
                process.terminate()
                break

    # Calculate average
    if len(vals) > 0:
        data.append(np.average(vals))
    else:
        data.append(0)

# Plotting
plt.figure()
plt.plot(x, data, marker='o', color='orange')
plt.margins(0)
plt.xlabel("Size of memory(1000 MB)")
plt.ylabel("Average bandwidth(MB/s)")
plt.savefig("bandwidth-memory-correlation.png", dpi=227)
plt.show()
