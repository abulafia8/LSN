#!/bin/bash

input_file="../INPUT/INPUT_EXAMPLES/input.solid"
sed -i 's/^RUN\s*[0-9]*/RUN\t\t\t\t\t\t0/' "$input_file"
sed -i 's/^RESTART\s*1/RESTART\t\t\t\t\t0/' "$input_file"

input_file="../INPUT/INPUT_EXAMPLES/input.liquid"
sed -i 's/^RUN\s*[0-9]*/RUN\t\t\t\t\t\t0/' "$input_file"
sed -i 's/^RESTART\s*1/RESTART\t\t\t\t\t0/' "$input_file"

input_file="../INPUT/INPUT_EXAMPLES/input.gas"
sed -i 's/^RUN\s*[0-9]*/RUN\t\t\t\t\t\t0/' "$input_file"
sed -i 's/^RESTART\s*1/RESTART\t\t\t\t\t0/' "$input_file"



