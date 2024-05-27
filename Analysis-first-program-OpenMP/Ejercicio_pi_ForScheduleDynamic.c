#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;
double step;

int main() {
    double pi;
    int max_threads = 8;
    int num_runs = 5;

    printf("Thread Count\tAverage Runtime\t\tPi\n");

    for (int thread_count = 1; thread_count <= max_threads; thread_count++) {
        double total_avg = 0.0;
        omp_set_num_threads(thread_count); 

        for (int run = 0; run < num_runs; run++) {

            double start_time, run_time;
            double final_sum = 0.0;
            int i;

            step = 1.0 / (double)num_steps;
            start_time = omp_get_wtime(); 

            double sum = 0.0;
            int ID = omp_get_thread_num();
            int num_threads = omp_get_num_threads();

            #pragma omp parallel for reduction(+:sum) schedule(dynamic)
            for (i = ID; i < num_steps; i += num_threads) {
                double x = (i + 0.5) * step;
                sum += 4.0 / (1.0 + x * x);
            }

            #pragma omp critical
            final_sum += sum;

            pi = step * final_sum;
            run_time = omp_get_wtime() - start_time;

            total_avg += run_time;
            
        }

        double average_runtime = total_avg / num_runs;
		printf("%d\t\t%.6lf seconds\t%.6lf\n", thread_count, average_runtime, pi);

    }

    

    return 0;
}

