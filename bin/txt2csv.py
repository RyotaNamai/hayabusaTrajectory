#!/usr/bin/python3

import os
import sys
from datetime import datetime
import pandas as pd

def main():
    datapath = sys.argv[1]
    with open(datapath, 'r') as f:
        data = f.readlines()
    data = [line for line in data if line[0] != '#']
    data = [line.split() for line in data]
    # print(data)
    headers = ['UTC', 'L+', 'X_hayabusa', 'Y_hayabusa', 'Z_hayabusa', 'X_earth', 'Y_earth', 'Z_earth', 'X_ryugu', 'Y_ryugu', 'Z_ryugu', 'Rs', 'Re', 'Ra', 'Vs', 'Ve', 'alpha', 'delta', 'Dflt']
    df = pd.DataFrame(data, columns=headers)
    df.to_csv(datapath[:-4]+'.csv', index=False, header=True)

if __name__ == "__main__":
    main()