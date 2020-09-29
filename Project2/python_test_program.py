import numpy as np
import matplotlib.pyplot as plt


class LinSys:

    def __init__(self, tol, iter, N, maxnondiag, maxiter, rho_max=5):
        self.tol = tol
        self.iter = iter
        self.N = N
        self.maxnondiag = maxnondiag
        self.maxiter = maxiter
        self.A = np.zeros((N,N))
        self.R = np.eye(N)
        self.rho = np.linspace(0, rho_max, N+1)
        self.eig = np.zeros(N)
        self.rho_max = rho_max
        self.p = None
        self.q = None

    def setH(self, d=True):
        if d:
            self.h = 1/(self.N+1)
        else:
            self.h = self.rho_max/(self.N+1)
        
        self.hh = self.h**2

    def fillMatrix1(self):

        self.setH(True)

        hh = self.hh

        for i in range(1, self.N):

            self.A[i,i] = 2/hh
            self.A[i,i-1] = -1/hh
            self.A[i-1,i] = -1/hh
        
        self.A[0,0] = 2/hh
    
    def fillMatrix2(self):

        self.setH(False)

        hh = self.hh

        for i in range(1, self.N):

            self.A[i,i] = 2/hh + rho[i]**2
            self.A[i,i-1] = -1/hh
            self.A[i-1,i] = -1/hh
        
        self.A[0,0] = 2/hh + self.rho[0]**2


    def offdiag(self, n):

        max = 0

        for i in range(0, n):

            for j in range(i+1, n):

                aij = abs(self.A[i,j])

                if aij > max:

                    max = aij
                    self.p = i
                    self.q = j

        self.maxnondiag = max

    def jacobi_rotate(self, n):

        A = self.A
        R = self.R

        p = self.p
        q = self.q

        if A[p,q] != 0.0:

            tau = (A[q,q] - A[p,p])/(2*A[p,q])

            if tau >= 0:

                t = 1.0/( tau + np.sqrt( 1.0 + tau**2 ) )

            else:

                t = -1.0/( -tau + np.sqrt( 1.0 + tau**2 ) )

            c = 1/np.sqrt(1 + t**2)
            s = c*t
        
        else:

            c = 1.0
            s = c*t

        a_pp = A[p,p]
        a_qq = A[q,q]

        A[p,p] = c**2 * a_pp - 2*c*s*A[p,q] + s**2 * a_qq
        A[q,q] = s**2 * a_pp + 2*c*s*A[p,q] + c**2 * a_qq

        A[p,q] = 0
        A[q,p] = 0

        R[p,p] = c
        R[q,q] = c
        R[p,q] = -s
        R[q,p] = s

        for i in range(0, n):

            if (i != p) and (i != q):

                a_ip = A[i,p]
                a_iq = A[i,q]

                A[i,p] = c*a_ip - s*a_iq
                A[p,i] = A[i,p]

                A[i,q] = c*a_iq + s*a_ip
                A[q,i] = A[i,q]
            
            r_ip = R[i,p]
            r_iq = R[i,q]

            R[i,p] = c*r_ip - s*r_iq
            R[i,q] = c*r_iq - s*r_ip

    def iterations(self):

        while (self.maxnondiag > self.tol) and (self.iter <= self.maxiter):

            self.offdiag(self.N)
            self.jacobi_rotate(self.N)
            self.iter += 1

    def extract_eigvals(self):
        eig = self.eig

        for i in range(0, self.N):
            eig[i] = self.A[i,i]

    def print_eigvals(self):

        self.extract_eigvals()

        for i in self.eig:
            print(i)
        
                
        
if __name__ == "__main__":

    test_obj = LinSys(1e-10, 0, 10, 1, 1e+6, 5)

    test_obj.fillMatrix1()

    print(np.linalg.eigvals(test_obj.A))

    test_obj.iterations()

    test_obj.print_eigvals()