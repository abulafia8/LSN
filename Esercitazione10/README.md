# Numerical Exercise 10

Similarly as for Numerical Exercise 9, the command to execute the code and correctly store the output is

```bash
./run.sh Independent
```
for an independent search, or
```bash
./run.sh Migrations
```
for a search with migrations

They both run the search with 8 cores

**About the code**: the 
```bash
SOURCE/GA
```
folder contains a slightly slimmer version of the GA code of Numerical Exercise 9, with a few more comments too.\
The
```bash
SOURCE/EX9_PARAL
```
folder is completely independents and contains a parallelization of Numerical Exercise 9, for which I didn't get any notable results (presumably due to the comparatively low dimensionality of the problem)