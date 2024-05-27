

#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;
double step;
int total_sum[7];

int main() {
	double pi;
	int num_threads = 8; 
    int num_runs = 5; 
    printf("Thread Count\tAverage Runtime\t\tPi\n");

    for (int thread_count = 1; thread_count <= num_threads; thread_count++) {
        double total_avg = 0.0;
        omp_set_num_threads(thread_count);

        for (int run = 0; run < num_runs; run++) {
            
        	double start_time, run_time;
            double final_sum = 0.0;
            int i;

            step = 1.0 / (double)num_steps;
            start_time = omp_get_wtime();

            int thread_gl = 0;
            double x = 0;

            #pragma omp parallel
            {
                int ID = omp_get_thread_num();
                int thread = omp_get_num_threads();

                if (ID == 0) {
                    thread_gl = thread;
                }

                double sum = 0.0;
                int i = 0;

                for (i = ID; i <= num_steps; i += thread) {
                    x = (i + 0.5) * step;
                    sum = sum + 4.0 / (1.0 + x * x);
                }
                total_sum[ID] = sum;


				#pragma omp critical
				{
					final_sum += sum;
				}
            }


            pi = step * final_sum;
            run_time = omp_get_wtime() - start_time;
            total_avg += run_time;
            
        }

        double average_runtime = total_avg / num_runs;
        printf("%d\t\t%.6lf seconds\t%.6lf\n", thread_count, average_runtime, pi);
        printf("\n");
    }
	return 0;
}


