# Numerical Exercise 7

To run **MC NVT** simulations the command is either one of

```bash
bash ./runs_mc_gas.sh 
```
```bash
bash ./runs_mc_liquid.sh 
```
```bash
bash ./runs_mc_solid.sh 
```

To run **MD NVE** simulations, to compare the results for the $g(r)$

```bash
bash ./runs_md_gas.sh 
```
```bash
bash ./runs_md_liquid.sh 
```
```bash
bash ./runs_md_solid.sh 
```

The file 

```bash
phase.dat
```
is modified by the script and contains the word that is picked up to feed the correct input and label the output files
