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

    def __str__(self):
        return f"{self.name}"

class ReadFile:

    def __init__(self):
        self.N = None
        self.T = None
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
            self.T = myFile.readline()

            #lst = list()

            r = myFile.read()
            print(r)

            for line in r.split():
                print(line)

                if line != "-":

                    name = line

                else:

                    self.planets.append(Planets(name, self.N))


            #print(self.planets)



    def plot(self):

        fig = plt.figure(figsize=(6,6))
        planet = self.planets
        size = len(self.planets)
        for i in range(size):

            if (i == 0):
                #plt.scatter(planet[i].pos[:,0], planet[i].pos[:,1], c="orange", s=30, label=f"{planet[i].name}")
                plt.plot(planet[i].pos[:,0], planet[i].pos[:,1], label=f"{planet[i].name}")

            else:
                plt.plot(planet[i].pos[:,0], planet[i].pos[:,1], label=f"{planet[i].name}")


        plt.title(f"Simulation of Solarsystem with n = {self.N} and T = {self.T}")
        plt.xlabel("x (AU)")
        plt.ylabel("y (AU)")
        plt.legend()
        plt.savefig("planets_all_2d_verlet_100.png")
        plt.show()

    def plot3D(self):

        fig = plt.figure()
        axes = plt.gca(projection='3d')
        axes.set_xlabel("x")
        axes.set_ylabel("y")
        axes.set_zlabel("z")
        #axes.axis("equal")
        planet = self.planets
        size = len(self.planets)
        for i in range(size):

            if (i == 0):
                axes.scatter(planet[i].pos[:,0], planet[i].pos[:,1], planet[i].pos[:,2], ".", c="orange", s=30, label=f"{planet[i].name}")


            else:
                axes.plot(planet[i].pos[:,0], planet[i].pos[:,1], planet[i].pos[:,2], label=f"{planet[i].name}")


        plt.title(f"Simulation of Solarsystem with n = {self.N} and T = {self.T}")
        plt.legend()
        plt.savefig("planets_all_3d_euler_100.png")
        plt.show()



if __name__ == "__main__":

    p = sys.argv[1]

    test_obj = ReadFile()
    test_obj.read_info("plot_info.txt")
    test_obj.read_values("values.txt")

    if p == "2d":

        test_obj.plot()
    else:

        test_obj.plot3D()

    plt.show()
