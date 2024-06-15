# Numerical Exercise 2

For the **imporance sampling** part, the library
```bash
SOURCE/LibIntegration.cc
```
does the bulk of the work. The class
```bash
SOURCE/Distribution.cc
```
is just a struct really

For the **random walks** part both the file

```bash
SOURCE/ContRW.cpp
```
and 
```bash
SOURCE/DiscrRW.cpp
```
contain at the beginning a short description of what the algroithm does

The function
```bash
MediaDistBlock
```
is instrumental in monitoring the average distance made by all the walkers and producing the stochastic variables to analyze