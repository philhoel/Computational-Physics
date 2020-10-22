import matplotlib.pyplot as plt
import os
import sys

class Planets:

    def __init__(self, name, ID, n):
        self.n = n
        self.pos = np.zeros((n,2))
        self.vel = np.zeros((n,2))
        self.acc = np.zeros((n,2))

        self.name = name
        self.ID = ID


class ReadFile:

    def __init__(self):
        self.N = None
        self.step = None
        self.planets = list()

    def read_values(self, filename):
        i = 0
        j = 0
        with open(filename) as myFile:
            for line in myFile:
                if line != "-":
                    x, y, vx, vy, ax, ay = line.split(" ")
                    self.planets[i].pos[j,0] = float(x)
                    self.planets[i].pos[j,1] = float(y)
                    self.planets[i].vel[j,0] = float(vx)
                    self.planets[i].vel[j,1] = float(vy)
                    self.planets[i].acc[j,0] = float(ax)
                    self.planets[i].acc[j,1] = float(ay)
                else:
                    i += 1
        

    def read_info(self, filename):
        
        with open(filename) as myFile:
            self.N = myFile.readline()
            self.step = myFile.readline()
            myFile.readline()

            for line in myFile:
                if line != "-":
                    id, name = line.split().strip()
                else:
                    self.planets.append(Planets(name, int(id), n))


    def plot(self):
        for planet in self.planets:
            plt.plot(planet.pos[:,0], planet.pos[:,1])
        
        plt.savefig("planets.png")
        plt.show()


if __name__ == "__main__":

    test_obj = ReadFile()
    test_obj.read_info("plot_info.txt")
    test_obj.read_values("values.txt")
    test_obj.plot()
    plt.show()