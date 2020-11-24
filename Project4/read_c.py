import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys
import os

f = sys.argv[1]

df = pd.read_csv(f)

def func(temp):
    E = [-8, 8, -8]
    sum = 0
    for i in E:
        #print("E: ", i)
        #print("sum: ", sum)
        sum += (1/(4*np.cosh(8/temp) + 12))*i*np.exp(-i/temp)

    return sum

anal = []
i = 0
temp = 1
final_t = 5
while temp <= final_t:
    #print(func(temp))
    anal.append(func(temp))
    temp += 0.05
    i += 1


plt.plot(df.iloc[:,4], anal)
plt.show()


plt.plot(df.iloc[:,4], df.iloc[:,0])
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Mean Energy $\langle E \rangle$")
#plt.savefig("average_E_f.png")
plt.show()

plt.plot(df.iloc[:,4], df.iloc[:,1])
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Mean Magnetization $\langle |M| \rangle$")
#plt.savefig("average_M_f.png")
plt.show()

plt.plot(df.iloc[:,4], df.iloc[:,2])
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Specific heat $C_V$")
#plt.savefig("Cv_f.png")
plt.show()

plt.plot(df.iloc[:,4], df.iloc[:,3])
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Suceptability \chi")
#plt.savefig("X_f.png")
plt.show()