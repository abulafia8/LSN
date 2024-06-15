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


def PlotLengths(type, n_cores):
    plt.figure(figsize=(10,5.5))
    l = read('OUTPUT/Lengths' + type + str(0) + '.dat')[0]
    x = np.arange(len(l))+1
    plt.plot(x, l, label='core ' + str(1))
    min_l = l[-1]
    
    for i in range(1, n_cores):
        l = read('OUTPUT/Lengths' + type + str(i) + '.dat')[0]
        x = np.arange(len(l))+1
        plt.plot(x, l, label='core ' + str(i+1))
        if l[-1] < min_l:
            min_l = l[-1]
            
    plt.xlabel('Generation')
    plt.ylabel('BestLength')
    plt.legend()
    plt.grid(True)
    plt.title(type)
    plt.show()
    
    print("Best Length: ", min_l)
    
def PlotPath(type):
    plt.figure(figsize=(7.5,7.5))
    data = np.genfromtxt('OUTPUT/Best' + type + '.dat')
    x = data[::, 0]  
    y = data[::, 1]  
    
    plt.plot(x[0], y[0], marker ="o",color = "r", markersize = 14)
    plt.plot(x, y)
    mappa = read('OUTPUT/Map.dat')
    plt.scatter(mappa[0], mappa[1], color = 'r')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.grid()
    plt.title(type)
    plt.show()

    
    
    

    
    