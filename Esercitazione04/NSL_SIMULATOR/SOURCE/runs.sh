#!/bin/bash

#chiamato più volte in successione esegue restart di simulazioni per fase specificata da terminale ad es.
# bash ./runs.sh solid
# bash ./runs.sh liquid
#bash ./runs.sh gas
#per ripartire dall'inizio eseguire lo script reset_runs.sh (è "buona prassi" eseguire questo comando prima di iniziare a fare run)

#occorre aver installato bc e avere il permesso riportato
# sudo apt-get install bc
# chmod -x runs.sh




#legge da linea di comando la fase da simulare, eventualmente modifica il file phase.dat
phase="$1"
phase_file="../INPUT/phase.dat"
if ! grep -q "$phase" "$phase_file"; then
    sed -i "s/^\S\+$/$(echo "$phase")/" "$phase_file"
fi
run=$(grep '^RUN' "../INPUT/INPUT_EXAMPLES/input.$phase" | awk '{print $2}')

./simulator.exe $

wait

#aggiorna il valore di restart qualora ce ne fosse bisogno e incrementa di uno il valore di run
sed -i '/^RUN/s/\(^\s*RUN\s*\)\([0-9]*\)/echo "\1$((\2+1))"/e' "../INPUT/INPUT_EXAMPLES/input.$phase"  
sed -i 's/RESTART\s\+0/RESTART        1/' "../INPUT/INPUT_EXAMPLES/input.$phase"

#modifica il nome dei file appena prodotti per enumerarli
PHASE=$(echo "$phase" | tr '[:lower:]' '[:upper:]')
cd ../OUTPUT/$PHASE
mv kinetic_energy.dat kinetic_energy$run.dat
mv potential_energy.dat potential_energy$run.dat
mv pressure.dat pressure$run.dat
mv temperature.dat temperature$run.dat
mv total_energy.dat total_energy$run.dat

