#!/bin/bash

usage() {
    echo "Usage: $0 <word>"
    echo "The type of execution must be either 'Migrations' or 'Independent'"
    exit 1
}
# Check
if [ "$#" -ne 1 ]; then
    usage
fi

word=$1
if [ "$word" != "Migrations" ] && [ "$word" != "Independent" ]; then
    usage
fi

mpiexec -n 8 ./Province "$word"

# Check and wait
if [ $? -ne 0 ]; then
    echo "Error: mpiexec command failed"
    exit 1
fi

# Rename 
for i in {0..7}; do
    mv "../OUTPUT/Lengths${i}.dat" "../OUTPUT/Lengths${word}${i}.dat"
done

mv "../OUTPUT/Best.dat" "../OUTPUT/Best${word}.dat"

# Si potrebbe far andare con un numero sempre maggiore di nodi

