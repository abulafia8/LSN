# Numerical Exercise 9

Please run the command

```bash
make
```
to execute the program type 
```bash
./Main Square
```
for cities randomly placed inside a square or

```bash
./Main Circle
```
for cities on a circle.

Please use the command
```bash
./run.sh Square
```

or 

```bash
./run.sh Circle
```
to produce output files that integrate with the notebook.

The code is thought to be run a single time and the generator is initialized on the
```bash
SOURCE/RNG/seed.in
```
file, even though modifying the main to

```bash
Initialize(&rnd, 1)
```
is possible and gives an execution with a different seed. Reproducibility is ensured by the 

```bash
SaveSeed
```
method at the end