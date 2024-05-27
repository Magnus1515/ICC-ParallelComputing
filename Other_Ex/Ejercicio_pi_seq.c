#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int num_samples = 1000000000; // Number of random samples (you can adjust this)
    int inside_circle = 0;
    double x, y, pi;
    clock_t start, end;
    
    // Get the current time (start)
    start = clock();

    // Seed the random number generator with the current time
    srand(time(NULL));

    for (int i = 0; i < num_samples; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }

    pi = 4.0 * (double)inside_circle / num_samples;

    // Get the current time (end)
    end = clock();
    
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Approximated value of pi: %f\n", pi);
    printf("Time taken to calculate (seconds): %f\n", cpu_time_used);

    return 0;
}
