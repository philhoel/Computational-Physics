import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import pandas as pd
import os
import sys
from mpl_toolkits.mplot3d import Axes3D
import matplotlib as mpl


t1 = sys.argv[1]
t2 = sys.argv[2]
t3 = sys.argv[3]
t4 = sys.argv[4]
df1 = pd.read_csv(sys.argv[5])
df2 = pd.read_csv(sys.argv[6])
df3 = pd.read_csv(sys.argv[7])
df4 = pd.read_csv(sys.argv[8])

#for df in filenames:
#    df = df.append(pd.Series(0, index=df.columns), ignore_index=True)
#print(filenames[5].shape)
x1, y1 = df1.shape
x, y = np.meshgrid(np.linspace(0,1,x1+1), np.linspace(0,1,y1))


fig = plt.figure(figsize=plt.figaspect(0.5))

ax = fig.add_subplot(2, 2, 1)
surf = ax.pcolormesh(x, y, df1, cmap="hot", vmin=0, vmax=1)
plt.title(f"Time = {t1}")
plt.ylabel("Y-axis")
fig.colorbar(surf)

ax = fig.add_subplot(2, 2, 2)
surf = ax.pcolormesh(x, y, df2, cmap="hot", vmin=0, vmax=1)
plt.title(f"Time = {t2}")
fig.colorbar(surf)

ax = fig.add_subplot(2, 2, 3)
surf = ax.pcolormesh(x, y, df3, cmap="hot", vmin=0, vmax=1)
plt.title(f"Time = {t3}")
fig.colorbar(surf)

ax = fig.add_subplot(2, 2, 4)
surf = ax.pcolormesh(x, y, df4, cmap="hot", vmin=0, vmax=1)
plt.title(f"Time = {t4}")
plt.xlabel("X-axis")
fig.colorbar(surf)

plt.tight_layout()
plt.savefig("buring_plate.png")
plt.show()