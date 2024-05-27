#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NPOINTS 1000
#define MAXITER 1000

struct d_complex
{
    double r;
    double i;
};

struct d_complex c;
int numoutside = 0;

void testpoint(struct d_complex c);

int main()
{
    int max_threads = 8;
    int num_runs = 5;
    
    printf("Thread Count\tAverage Runtime\t\tArea\n");
    
    for (int thread_count = 1; thread_count <= max_threads; thread_count++)
    {
        double total_avg = 0.0;
        omp_set_num_threads(thread_count);

        for (int run = 0; run < num_runs; run++)
        {
            numoutside = 0; // Reset numoutside for each run
            double total_time = 0.0;
            
            #pragma omp parallel
            {
                int i, j;
                double eps = 1.0e-5;
                double start_time, run_time;
                int local_numoutside = 0;
                
                start_time = omp_get_wtime();
                
                #pragma omp for schedule(static)
                for (i = 0; i < NPOINTS; i++)
                {
                    for (j = 0; j < NPOINTS; j++)
                    {
                        c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
                        c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
                        testpoint(c);
                    }
                }
                
                #pragma omp single
                {
                    run_time = omp_get_wtime();
                    total_time += run_time;
                    local_numoutside = numoutside;
                }
            }
            
            double average_runtime = total_time / num_runs;
            double area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - local_numoutside) / (double)(NPOINTS * NPOINTS);
            
            total_avg += average_runtime;
            printf("%d\t\t%.6lf seconds\t%12.8f\n", thread_count, average_runtime, area);
        }
    }
}

void testpoint(struct d_complex c)
{
    struct d_complex z;
    int iter;
    double temp;

    z = c;
    for (iter = 0; iter < MAXITER; iter++)
    {
        temp = (z.r * z.r) - (z.i * z.i) + c.r;
        z.i = z.r * z.i * 2 + c.i;
        z.r = temp;
        if ((z.r * z.r + z.i * z.i) > 4.0)
        {
            numoutside++;
            break;
        }
    }
}
