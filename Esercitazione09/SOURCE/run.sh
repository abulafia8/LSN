#!/bin/bash

# chmod +x run.sh

type=$1

./Main "$type"

mv ../OUTPUT/Map.dat "../OUTPUT/Map${type}.dat"
mv ../OUTPUT/Lengths.dat "../OUTPUT/Lengths${type}.dat"
mv ../OUTPUT/Best.dat "../OUTPUT/Best${type}.dat"
