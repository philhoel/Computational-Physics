import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os
import sys

file1 = sys.argv[1]
file2 = sys.argv[2]
file3 = sys.argv[3]
file4 = sys.argv[4]
file5 = sys.argv[5]


PDE1 = pd.read_csv(file1)
PDE2 = pd.read_csv(file2)
PDE3 = pd.read_csv(file3)
PDE4 = pd.read_csv(file4)
PDE5 = pd.read_csv(file5)

print(PDE1.shape)
print(PDE4.shape)

xsize, tsize = PDE1.shape
x2size, t2size = PDE2.shape
x = np.linspace(0,1,xsize)
x2 = np.linspace(0,1,x2size)



#Forward Euler

plt.plot(x, PDE1.iloc[:,10], color="black",label="t = 0.001")
plt.plot(x, PDE1.iloc[:,50], color="green", label="t = 0.005")
plt.plot(x, PDE1.iloc[:,100], color="red", label="t = 0.01")
plt.plot(x, PDE1.iloc[:,500], color="blue", label="t = 0.05")
plt.plot(x, PDE1.iloc[:,900], color="purple", label="t = 0.09")


plt.plot(x, PDE4.iloc[:,10], "--", color="black")
plt.plot(x, PDE4.iloc[:,50], "--", color="green")
plt.plot(x, PDE4.iloc[:,100], "--", color="red")
plt.plot(x, PDE4.iloc[:,500], "--", color="blue")
plt.plot(x, PDE4.iloc[:,900], "--", color="purple")

plt.xlabel("x")
plt.ylabel("u(x,t)")
plt.title("Comparison of time steps - Forward Euler")
plt.legend()
plt.show()

#Backward Euler

plt.plot(x2, PDE2.iloc[:,10], color="black",label="t = 0.001")
plt.plot(x2, PDE2.iloc[:,50], color="green", label="t = 0.005")
plt.plot(x2, PDE2.iloc[:,100], color="red", label="t = 0.01")
plt.plot(x2, PDE2.iloc[:,500], color="blue", label="t = 0.05")
plt.plot(x2, PDE2.iloc[:,900], color="purple", label="t = 0.09")


plt.plot(x2, PDE5.iloc[:,10], "--", color="black")
plt.plot(x2, PDE5.iloc[:,50], "--", color="green")
plt.plot(x2, PDE5.iloc[:,100], "--", color="red")
plt.plot(x2, PDE5.iloc[:,500], "--", color="blue")
plt.plot(x2, PDE5.iloc[:,900], "--", color="purple")

plt.xlabel("x")
plt.ylabel("u(x,t)")
plt.title("Comparison of time steps - Backward Euler")
plt.legend()
plt.show()

#Crank-Nicoloson

plt.plot(x2, PDE3.iloc[:,10], color="black",label="t = 0.001")
plt.plot(x2, PDE3.iloc[:,50], color="green", label="t = 0.005")
plt.plot(x2, PDE3.iloc[:,100], color="red", label="t = 0.01")
plt.plot(x2, PDE3.iloc[:,500], color="blue", label="t = 0.05")
plt.plot(x2, PDE3.iloc[:,900], color="purple", label="t = 0.09")


plt.plot(x2, PDE5.iloc[:,10], "--", color="black")
plt.plot(x2, PDE5.iloc[:,50], "--", color="green")
plt.plot(x2, PDE5.iloc[:,100], "--", color="red")
plt.plot(x2, PDE5.iloc[:,500], "--", color="blue")
plt.plot(x2, PDE5.iloc[:,900], "--", color="purple")


plt.xlabel("x")
plt.ylabel("u(x,t)")
plt.title("Comparison of time steps - Crank-Nicolson")
plt.legend()
plt.show()