#!/bin/bash

# Set the name of your C program
program_name="linked2023"

# Set the number of runs
num_runs=1

# Loop through different thread counts
for num_threads in {1..8}; do
    echo "Running program with $num_threads threads"
    echo

    # Build the C program
    clang -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp -o linked2023 linked2023.c

    # Run the program
    ./"$linked2023" "$num_threads" "$num_runs"

    echo
done

echo "Done."
