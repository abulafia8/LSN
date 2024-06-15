from array import array
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math
from matplotlib.pyplot import figure

def read(file, columns=2):
    data = np.genfromtxt(file)
    if columns == 1:
        return data
    elif columns == 2:
        measure = data[::, 0]
        errors = data[::, 1]
        return measure, errors


def Plot(Ngens, map_type):
    plt.figure(figsize=(20,8))

    plt.subplot(1,2,1)
    res = read('OUTPUT/Best' + map_type + '.dat')
    plt.plot(res[0][0], res[1][0], marker ="o",color = "r", markersize = 14)
    plt.plot(res[0], res[1])
    mappa = read('OUTPUT/Map' + map_type + '.dat')
    plt.scatter(mappa[0], mappa[1], color = 'r')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.grid()

    plt.subplot(1,2,2)
    res = read('OUTPUT/Lengths' + map_type + '.dat')
    plt.plot(np.arange(Ngens)+1, res[0], label='Best')
    plt.plot(np.arange(Ngens)+1, res[1], label='Best Half')
    plt.xlabel("Generations")
    plt.ylabel("Length")
    plt.legend()

    plt.show()
    print('Best Length: ', res[0][-1])