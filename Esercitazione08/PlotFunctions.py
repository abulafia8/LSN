from array import array
import matplotlib
import matplotlib.pyplot as plt
from scipy.stats import chi2
from scipy.stats import norm
from scipy.optimize import curve_fit
import scipy.integrate as spi
import numpy as np
import math

def read(file, columns=2):
    data = np.genfromtxt(file)
    if columns == 1:
        return data
    elif columns == 2:
        measure = data[::, 0]
        errors = data[::, 1]
        return measure, errors

def PsiNum(x):
    a = 10
    N = 1000 
    x = np.linspace(-a/2, a/2, N)
    V = (x**2 - 2.5)*x**2
    CDiff = np.diag(np.ones(N-1),-1)-2*np.diag(np.ones(N),0)+np.diag(np.ones(N-1),1)
    H = (-CDiff)/(2*(x[1]-x[0])**2) + np.diag(V)
    E,psi = np.linalg.eigh(H)
    psi = np.transpose(psi) / np.sqrt(x[1]-x[0])
    return psi[0]**2

def PlotHist():
    positions = read('OUTPUT/Positions.dat', 1)
    hist, bins = np.histogram(positions, bins=120, density=False)
    hist_normalized = hist / (np.sum(hist) * (bins[1:] - bins[:-1]))
    plt.bar(bins[:-1], hist_normalized, width=(bins[1:] - bins[:-1]), align='edge')
    plt.title("Optimized Wavefunction")
    
def PlotEnergies():
    res = read('OUTPUT/Energies.dat')
    fig = plt.figure(figsize=(15, 6))
    AnnSteps = 10     #steps in un singolo ciclo di annealing
    arr = res[0][::AnnSteps]
    err = res[1][::AnnSteps]
    b_step = 1.5
    beta = np.arange(1, 1 + 200 * b_step, b_step)

    plt.errorbar(beta, arr, yerr=err, label='H')
    plt.xlabel('beta')
    plt.ylabel('H')
    plt.grid()
    plt.title('Energy')
    plt.axhline(y = -0.46, color = 'r', label='Actual GS Energy') 
    plt.legend()
    plt.show()