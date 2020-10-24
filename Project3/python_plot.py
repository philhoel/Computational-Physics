import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import numpy as np
import os
import sys

class Planets:

    def __init__(self, name, n):
        self.n = n
        self.pos = np.zeros((n-1,3))
        self.vel = np.zeros((n-1,3))
        self.acc = np.zeros((n-1,3))

        self.name = name


class ReadFile:

    def __init__(self):
        self.N = None
        self.step = None
        self.planets = list()

    def read_values(self, filename):
        i = 0
        j = 0
        with open(filename) as myFile:

            myFile.readline()

            for line in myFile:

                line = line.strip()

                if line.strip() != str(chr(45)):

                    x, y, z, vx, vy, vz, ax, ay, az = line.split()
                    self.planets[i].pos[j,0] = float(x)
                    self.planets[i].pos[j,1] = float(y)
                    self.planets[i].pos[j,2] = float(z)
                    self.planets[i].vel[j,0] = float(vx)
                    self.planets[i].vel[j,1] = float(vy)
                    self.planets[i].vel[j,2] = float(vz)
                    self.planets[i].acc[j,0] = float(ax)
                    self.planets[i].acc[j,1] = float(ay)
                    self.planets[i].acc[j,2] = float(az)
                    j += 1

                else:

                    i += 1
                    j = 0
        

    def read_info(self, filename):
        
            myFile = open(filename)
            self.N = int(myFile.readline())
            self.step = myFile.readline()

            #lst = list()

            r = myFile.read()
            print(r)

            for line in r.split():
                print(line)
                
                if line != "-":

                    name = line

                else:

                    self.planets.append(Planets(name, self.N))
                    

            print(self.planets)
            


    def plot(self):

        fig = plt.figure()
        axes = plt.axes(projection='3d')
        axes.set_xlabel("x")
        axes.set_ylabel("y")
        axes.set_zlabel("z")
        axes.axis("equal")
        for planet in self.planets:

            axes.plot3D(planet.pos[:,0], planet.pos[:,1], label=f"{planet.name}")
        
        
        
        plt.legend()
        plt.savefig("planets.png")
        plt.show()


if __name__ == "__main__":

    test_obj = ReadFile()
    test_obj.read_info("plot_info.txt")
    test_obj.read_values("values.txt")
    test_obj.plot()
    plt.show()