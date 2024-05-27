#!/bin/bash

# Number of runs
NUM_RUNS=5

# Number of threads
NUM_THREADS=8

# Compile the C code with OpenMP support using clang
clang -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp -o linked2023 linked2023.c

# Check if compilation is successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Array to store execution times for each thread
declare -a thread_execution_times

# Run the program multiple times
for ((i=1; i<=$num; i++)); do
    echo "Run $i"
    
    # Run the program and capture the execution time for each thread
    thread_execution_time=$(./linked2023 | grep "Compute Time" | awk '{print $3}')
    thread_execution_times+=("$thread_execution_time")

    # Sleep for a moment to avoid potential issues with rapid execution
    sleep 1
done

# Calculate the average for each thread
for ((i=0; i<$NUM_THREADS; i++)); do
    total_time=0
    for ((j=$i; j<${#thread_execution_times[@]}; j+=$NUM_THREADS)); do
        total_time=$(echo "$total_time + ${thread_execution_times[j]}" | bc)
    done
    average_time=$(echo "scale=4; $total_time / $NUM_RUNS" | bc)
    echo "Average Compute Time for Thread $i over $NUM_RUNS runs: $average_time seconds"
done
