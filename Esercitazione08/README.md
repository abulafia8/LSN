# Numerical Exercise 8

The order of execution was thought as follows:

```bash
./Exercise1.2 
```

to optimize the parameters in the wavefunction, followed by

```bash
./Exercise1.1 
```

to retrieve the results for the hamiltonian. However the file

```bash
INPUT/InitialParameters.dat
```
which contains the final result of the optimization process, already contains the result.

**A few words on the code**: the class

```bash
SOURCE/Walker.cc
```
was originally conceived to give both the possibility of taking annealing steps **and** wavefunction sampling steps. We make use of this feature in the final step of the optimization, but in order to incorporate the uncertainties on the energy, the ad-hoc method
```bash
MoveAndTrack
```
is used