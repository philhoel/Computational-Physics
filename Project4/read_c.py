import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys
import os

f = sys.argv[1]

df = pd.read_csv(f)

def meanE(temp):
    Z = 4*np.cosh(8/temp) + 12
    zum = -32*np.sinh(8/temp)/Z

    return zum

def meanE2(temp):
    Z = 4*np.cosh(8/temp) + 12
    zum = 256*np.sinh(8/temp)/Z

    return zum

def meanM(temp):
    Z = 4*np.cosh(8/temp) + 12
    zum = 8*((2+np.exp(8/temp))/Z)
    return zum

def meanM2(temp):
    Z = 4*np.cosh(8/temp) + 12
    zum = 32*((1 + np.exp(8/temp))/Z)
    return zum



E = []
E2 = []
M = []
M2 = []
Cv = []
X = []
for i in df.iloc[:,4]:
    E.append(meanE(i)/4)
    E2.append(meanE2(i)/16)
    M.append(meanM(i)/4)
    M2.append(meanM2(i)/16)
    Cv.append((meanE2(i) - meanE(i)*meanE(i))/(i**2))
    X.append((meanM2(i) - meanM(i)*meanM(i))/i)




plt.plot(df.iloc[:,4], df.iloc[:,0], ".", label=r"$\langle E \rangle$")
plt.plot(df.iloc[:,4], E, label="E")
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Mean Energy $\langle E \rangle$")
plt.savefig("average_E_c.png")
plt.show()

plt.plot(df.iloc[:,4], df.iloc[:,1], ".", label=r"$\langle |M| \rangle$")
plt.plot(df.iloc[:,4], M, label="|M|")
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Mean Magnetization $\langle |M| \rangle$")
plt.savefig("average_M_c.png")
plt.show()

plt.plot(df.iloc[:,4], df.iloc[:,2], ".", label=r"$C_V$")
plt.plot(df.iloc[:,4], Cv, label=r"$C_V (analytic)$")
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"Specific heat $C_V$")
plt.savefig("Cv_c.png")
plt.show()

plt.plot(df.iloc[:,4], df.iloc[:,3], ".", label=r"$\chi$")
plt.plot(df.iloc[:,4], X, label=r"$\chi$ (analytic)")
plt.legend()
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel(r"$Suceptability \chi$")
plt.savefig("X_c.png")
plt.show()


plt.plot(df.iloc[:,4], df.iloc[:,5])
plt.xlabel(r"Temparature [T][$J/k_B$]")
plt.ylabel("Accepted Configurations")
plt.savefig("Acc_temp.png")
plt.show()