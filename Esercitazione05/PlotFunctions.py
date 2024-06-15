from array import array
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math
from matplotlib.pyplot import figure
from mpl_toolkits import mplot3d

def read(file, columns=2):
    data = np.genfromtxt(file)
    if columns == 2:
        measure = data[::, 0]
        errors = data[::, 1]
        return measure, errors
    elif columns == 3:
        x = data[::, 0]
        y = data[::, 1]
        z = data[::, 2]
        return x, y, z

def PlotCombined(state, step):
    # Read the data for both plots
    path_res = read('OUTPUT/Path' + state + step + '.dat', 3)
    r_res = read('OUTPUT/' + state + step + '.dat', 2)
    fig = plt.figure(figsize=(14, 6))

    ax1 = fig.add_subplot(121, projection='3d')
    start = 501
    n = 0
    if state == 'GroundState':
        n = 100000 + start
    elif state == 'ExcitedState':
        n = 10000 + start
    ax1.scatter(path_res[0][start:n],path_res[1][start:n],path_res[2][start:n],c=path_res[2][start:n],marker='.')
    ax1.set_xlabel('x ($a_0$)')
    ax1.set_ylabel('y ($a_0$)')
    ax1.set_zlabel('z ($a_0$)')
    ax1.view_init(10, 30)

    ax2 = fig.add_subplot(122)
    x = np.arange(len(r_res[0])) + 1
    ax2.errorbar(x, r_res[0], yerr=r_res[1])
    ax2.set_xlabel('blocks')
    ax2.set_ylabel('$ r  (a_0) $')
    ax2.set_title("Radius")
    if state == 'GroundState':
        ax2.axhline(y=1.5, color='r')
    if state == 'ExcitedState':
        ax2.axhline(y=5, color='r')
    ax2.grid()

    plt.show()
    
    print('Result = ', r_res[0][len(r_res[0])-1]) 
    print('Error = ', r_res[1][len(r_res[0])-1]) 