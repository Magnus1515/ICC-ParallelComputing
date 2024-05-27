#!/bin/bash

# Number of runs
NUM_RUNS=5

# Number of threads
NUM_THREADS=8

# Compile the C code
gcc -o linked2023 linked2023.c -fopenmp -lm

# Array to store execution times
declare -a execution_times

# Run the program multiple times
for ((i=1; i<=$NUM_RUNS; i++)); do
    echo "Run $i"
    
    # Run the program and capture the execution time
    execution_time=$(./linked2023 | grep "Compute Time" | awk '{print $3}')
    execution_times+=("$execution_time")

    # Sleep for a moment to avoid potential issues with rapid execution
    sleep 1
done

# Calculate the average for each thread
total_time=0
for time in "${execution_times[@]}"; do
    total_time=$(echo "$total_time + $time" | bc)
done

average_time=$(echo "scale=4; $total_time / $NUM_RUNS" | bc)

echo "Average Compute Time for $NUM_THREADS threads over $NUM_RUNS runs: $average_time seconds"
