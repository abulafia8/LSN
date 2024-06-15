# Numerical Exercise 4

Run either one of the commands

```bash
bash ./runs.sh solid
```
```bash
bash ./runs.sh liquid
```
```bash
bash ./runs.sh gas
```
to simulate the phase that you want. The script modifies the relevant file in the folder

```bash
INPUT_EXAMPLES
```

If you run the command multiple times, the simulation will pick up from where it started

It is a good idea to first run the command

```bash
bash ./reset_runs.sh 
```
in order to set the restart label to 0 and the number of runs (which enumerate the output files, added ad hoc) to 0

The file 

```bash
phase.dat
```
is modified by the script if needed and contains the word that is picked up to feed the correct input file and label the output files