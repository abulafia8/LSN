#!/bin/bash

#inserire da linea di comando il tipo di campionamento: la modalità d'uso è

#bash ./runs.sh METROPOLIS oppure bash ./runs.sh GIBBS

#fa un ciclo sulle varie temperature. se il campo magnetico è acceso calcola solo la magnetizzazione, in caso contrario il resto

#limitazione: si integra bene con il notebook solo se i valori della temperatura sono quelli indicati (troncamento delle cifre decimali)


#modifiche input secondo istruzioni
echo -e "\nBE CAREFUL: if you want to measure magnetization it is YOUR duty to turn on the magnetic field \n\n
NO NEED to worry about the properties.dat file, it will take care of itself"
echo "if you are not interested in magnetization remember to turn the magnetic field off"

#si potrebbe inserire maipolazione di properties

SAMPLING="$1"
if [ "$SAMPLING" = "METROPOLIS" ]; then
    sed -i 's/SIMULATION_TYPE\s\+3/SIMULATION_TYPE                2/' ../INPUT/input.dat
elif [ "$SAMPLING" = "GIBBS" ]; then
    sed -i 's/SIMULATION_TYPE\s\+2/SIMULATION_TYPE                3/' ../INPUT/input.dat
fi

TEMP=$(grep "TEMP" ../INPUT/input.dat | awk '{print $2}')
if [ TEMP != 0.5 ]; then
    TEMP=0.5
    sed -i "s/^\(TEMP\s*\)[0-9.]*$/\1$TEMP/" ../INPUT/input.dat
fi

#esecuzione
#se il campo magnetico è diverso da zero accende check. quando check è acceso solo la magnetizzazione viene manipolata
line_number=$(grep -n "SIMULATION_TYPE" ../INPUT/input.dat | cut -d: -f1)
h=$(awk -v line=$line_number 'NR==line {print $4}' ../INPUT/input.dat)
if [ "$h" != "0.0" ]; then
    check=1
fi

if [ "$check" == "1" ]; then
    file_properties="../INPUT/properties.dat"
    new_properties="MAGNETIZATION"
    > "$file_properties"
    echo -e "$new_properties" > "$file_properties"

    while (( $(echo "$TEMP <= 2.0" | bc -l) )); do

    ./simulator.exe &
    wait 

    cd ../OUTPUT/MAGNETIZATION
    mv magnetization.dat "$SAMPLING/magnetization$(printf "%.2f" "$TEMP" | sed 's/\.00$/.0/' | sed 's/\.50$/.5/').dat"
    cd ../../SOURCE

    TEMP=$(echo "$TEMP + 0.25" | bc -l)

    sed -i "s/^\(TEMP\s*\)[0-9.]*$/\1$TEMP/" ../INPUT/input.dat

    done
else
    file_properties="../INPUT/properties.dat"
    new_properties="TOTAL_ENERGY\nSPECIFIC_HEAT\nSUSCEPTIBILITY"
    > "$file_properties"
    echo -e "$new_properties" > "$file_properties"

    while (( $(echo "$TEMP <= 2.0" | bc -l) )); do

    ./simulator.exe &
    wait 

    cd ../OUTPUT/SPECIFIC_HEAT
    mv specific_heat.dat "$SAMPLING/specific_heat$(printf "%.2f" "$TEMP" | sed 's/\.00$/.0/' | sed 's/\.50$/.5/').dat"
    cd ../SUSCEPTIBILITY
    mv susceptibility.dat "$SAMPLING/susceptibility$(printf "%.2f" "$TEMP" | sed 's/\.00$/.0/' | sed 's/\.50$/.5/').dat"
    cd ../TOTAL_ENERGY
    mv total_energy.dat "$SAMPLING/total_energy$(printf "%.2f" "$TEMP" | sed 's/\.00$/.0/' | sed 's/\.50$/.5/').dat"
    cd ../../SOURCE

    TEMP=$(echo "$TEMP + 0.25" | bc -l)

    # update the value of the temperature in the file
    sed -i "s/^\(TEMP\s*\)[0-9.]*$/\1$TEMP/" ../INPUT/input.dat

    done

fi








