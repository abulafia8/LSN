#!/bin/bash

new_input="../INPUT/INPUT_EXAMPLES/input.liquid"
phase_file="../INPUT/phase.dat"

sed -i 's/SIMULATION_TYPE\s\+0/SIMULATION_TYPE        1/' "$new_input"
sed -i 's/TEMP\s\+1.978/TEMP                   1.1/' "$new_input"
sed -i 's/DELTA\s\+0.0005/DELTA                 0.1/' "$new_input"
sed -i 's/NBLOCKS\s\+80/NBLOCKS                50/' "$new_input"
sed -i 's/NSTEPS\s\+1000/NSTEPS                 2000/' "$new_input"

if ! grep -q "liquid" "$phase_file"; then
    sed -i 's/^\S\+$/liquid/' "$phase_file"
fi

./simulator.exe &

wait

cd ../OUTPUT/LIQUID
mv gofr.dat gofrMC.dat
mv kinetic_energy.dat kinetic_energyMC.dat
mv potential_energy.dat potential_energyMC.dat
mv pressure.dat pressureMC.dat
mv temperature.dat temperatureMC.dat
mv total_energy.dat total_energyMC.dat