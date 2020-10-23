import numpy as np
import matplotlib.pyplot as plt

dt = 0.001

def func(m_s, m_e, r, x):
    g = 6.68e-11
    G = 4*np.pi**2
    F = -x*G/r**3
    return F

def verlet(f, n, m_s, m_e):

    x = np.zeros((n+1, 2))
    v = np.zeros((n+1, 2))
    a = np.zeros((n+1, 2))

    x[0,0] = 1
    x[0,1] = 0
    v[0,0] = 0
    v[0,1] = 2*np.pi

    for i in range(n):
        r = np.sqrt(x[i,0]**2 + x[i,1]**2)

        x[i+1, :] = x[i,:] + v[i,:]*dt + 0.5*(dt**2)*a[i,:]
        a[i+1,:] = f(m_s, m_e, r, x[i+1,:])
        v[i+1,:] = v[i,:] + dt*(a[i,:] + a[i+1,:])/2

    return x, v, a

def euler(f, n, m_s, m_e):

    x = np.zeros((n+1, 2))
    v = np.zeros((n+1, 2))
    a = np.zeros((n+1, 2))

    x[0,0] = 1
    x[0,1] = 0
    v[0,0] = 0
    v[0,1] = 2*np.pi

    for i in range(n):
        r = np.sqrt(x[i,0]**2 + x[i,1]**2)
        a[i,:] = f(m_s, m_e, r, x[i,:])
        v[i+1,:] = v[i,:] + a[i,:]*dt
        x[i+1,:] = x[i,:] + v[i,:]*dt

    return x, v, a

if __name__ == "__main__":

    m_e = 1
    m_s = 1

    n = 1000

    xv, vv, av = verlet(func, n, m_s, m_e)
    xe, ve, ae = euler(func, n, m_s, m_e)

    plt.plot(xv[:,0], xv[:,1], label="Verlet")
    plt.plot(xe[:,0], xe[:,1], label="Euler")
    plt.legend()
    plt.show()