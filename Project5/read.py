import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os
import sys

filename = sys.argv[1]


PDE = pd.read_csv(filename)

plt.pcolormesh(PDE)
plt.xlabel("Time")
plt.ylabel("Length of rod")
plt.colorbar()
plt.show()