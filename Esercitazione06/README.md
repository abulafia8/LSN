# Numerical Exercise 6

Run the command

```bash
bash ./runs.sh METROPOLIS
```

or

```bash
bash ./runs.sh GIBBS
```
to simulate the 1D Ising model for temperatures ranging from 0.5 to 2.0

The script acts on the file
```bash
input.dat
```
To suit the requests of the exercise, the command computes only the magnetization if the magnetic field is on\
It computes the other properties if it's off

**Equilibration** is performed in the main, as I have previously found that the magnetization stabilizes itself on zero, starting from a disordered (infinite temperature) state, about after half a block