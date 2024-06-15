#!/bin/bash

new_input="../INPUT/INPUT_EXAMPLES/input.liquid"
phase_file="../INPUT/phase.dat"

sed -i 's/SIMULATION_TYPE\s\+1/SIMULATION_TYPE        0/' "$new_input"
sed -i 's/TEMP\s\+1.1/TEMP                   1.978/' "$new_input"
sed -i 's/DELTA\s\+0.1/DELTA                  0.0005/' "$new_input"
sed -i 's/NBLOCKS\s\+50/NBLOCKS                80/' "$new_input"
sed -i 's/NSTEPS\s\+2000/NSTEPS                 1000/' "$new_input"

if ! grep -q "liquid" "$phase_file"; then
    sed -i 's/^\S\+$/liquid/' "$phase_file"
fi

./simulator.exe &

wait

cd ../OUTPUT/LIQUID
mv gofr.dat gofrMD.dat
mv kinetic_energy.dat kinetic_energyMD.dat
mv potential_energy.dat potential_energyMD.dat
mv pressure.dat pressureMD.dat
mv temperature.dat temperatureMD.dat
mv total_energy.dat total_energyMD.dat