
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <omp.h>

// #define NPOINTS 1000 // Increase the grid resolution
// #define MAXITER 1000 // Increase the number of iterations

// // void testpoint();

// struct d_complex
// {
//     double r;
//     double i;
// };

// struct d_complex c;
// int numoutside = 0;
// void testpoint(struct d_complex c);

// int main()
// {
//     int max_threads = 8;
//     int num_runs = 5;
//     double area, temp_area;
//     // printf("Thread Count\tAverage Runtime\t\tArea\n");
//     for (int thread_count = 1; thread_count <= max_threads; thread_count++)
//     {
//         double total_avg = 0.0;
//         omp_set_num_threads(thread_count);

//         for (int run = 0; run < num_runs; run++)
//         {

//             double total_avg = 0.0;
//             omp_set_num_threads(thread_count);
//             int i, j;
//             double error, eps = 1.0e-5;
//             double start_time, run_time;

//             start_time = omp_get_wtime();

// #pragma omp parallel for private(j, c, eps) schedule(static) default(none) reduction(+ : numoutside)
//             for (i = 0; i < NPOINTS; i++)
//             {
//                 for (j = 0; j < NPOINTS; j++)
//                 {
//                     c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
//                     c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
//                     testpoint(c);
//                 }
//             }

//             area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
//             error = area / (double)NPOINTS;

//             temp_area = area;
//             run_time = omp_get_wtime() - start_time;

//             total_avg += run_time;
//         }

//         double average_runtime = total_avg /num_runs;
//         printf("%d\t\t%.6lf seconds\t%12.8f\n", thread_count, average_runtime, temp_area);
//     }
// }

// void testpoint(struct d_complex c)
// {

//     // Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
//     // If loop count reaches MAXITER, point is considered to be inside the set

//     struct d_complex z;
//     int iter;
//     double temp;

//     z = c;
//     for (iter = 0; iter < MAXITER; iter++)
//     {
//         temp = (z.r * z.r) - (z.i * z.i) + c.r;
//         z.i = z.r * z.i * 2 + c.i;
//         z.r = temp;
//         if ((z.r * z.r + z.i * z.i) > 4.0)
//         {
// #pragma omp atomic
//             numoutside++;
//             break;
//         }
//     }
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <omp.h>

// #define NPOINTS 1000 // Increase the grid resolution
// #define MAXITER 1000 // Increase the number of iterations

// struct d_complex
// {
//     double r;
//     double i;
// };

// struct d_complex c;
// int numoutside = 0;
// void testpoint(struct d_complex c);

// int main()
// {
//     int max_threads = 8;
//     int num_runs = 5;
//     double area, temp_area;

//     printf("Thread Count\tAverage Runtime\t\tArea\n");

//     for (int thread_count = 1; thread_count <= max_threads; thread_count++)
//     {
//         double total_avg = 0.0;
//         omp_set_num_threads(thread_count);

//         for (int run = 0; run < num_runs; run++)
//         {
//             int i, j;
//             double error, eps = 1.0e-5;
//             double start_time, run_time;

//             start_time = omp_get_wtime();

//             #pragma omp parallel for private(j, c, eps) schedule(static) default(none) reduction(+ : numoutside)
//             for (i = 0; i < NPOINTS; i++)
//             {
//                 for (j = 0; j < NPOINTS; j++)
//                 {
//                     c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
//                     c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
//                     testpoint(c);
//                 }
//             }

//             area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
//             error = area / (double)NPOINTS;

//             run_time = omp_get_wtime() - start_time;

//             total_avg += run_time;
//             temp_area = area;
//         }

//         double average_runtime = total_avg / num_runs;
//         printf("%d\t\t%.6lf seconds\t%12.8f\n", thread_count, average_runtime, temp_area);
//     }
// }

// void testpoint(struct d_complex c)
// {

//     // Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
//     // If loop count reaches MAXITER, point is considered to be inside the set

//     struct d_complex z;
//     int iter;
//     double temp;

//     z = c;
//     for (iter = 0; iter < MAXITER; iter++)
//     {
//         temp = (z.r * z.r) - (z.i * z.i) + c.r;
//         z.i = z.r * z.i * 2 + c.i;
//         z.r = temp;
//         if ((z.r * z.r + z.i * z.i) > 4.0)
//         {
// #pragma omp atomic
//             numoutside++;
//             break;
//         }
//     }
// }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NPOINTS 1000 // Increase the grid resolution
#define MAXITER 1000 // Increase the number of iterations

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
    double total_area, temp_area;

    printf("Thread Count\tAverage Runtime\t\tArea\n");

    for (int thread_count = 1; thread_count <= max_threads; thread_count++)
    {
        double total_avg = 0.0;
        total_area = 0.0; // Initialize total_area
        omp_set_num_threads(thread_count);

        for (int run = 0; run < num_runs; run++)
        {
            int i, j;
            double error, eps = 1.0e-5;
            double start_time, run_time;

            start_time = omp_get_wtime();

#pragma omp parallel for private(j, c, eps) schedule(static) default(none) reduction(+ : numoutside) reduction(+ : total_area)
            for (i = 0; i < NPOINTS; i++)
            {
                for (j = 0; j < NPOINTS; j++)
                {
                    c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
                    c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
                    testpoint(c);
                }
            }

            error = temp_area / (double)NPOINTS; // Use temp_area here
            run_time = omp_get_wtime() - start_time;
            total_avg += run_time;
        }

        double average_runtime = total_avg / num_runs;
        printf("%d\t\t%.6lf seconds\t%12.8f\n", thread_count, average_runtime, total_area / num_runs);
    }
}

void testpoint(struct d_complex c)
{

    // Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
    // If loop count reaches MAXITER, point is considered to be inside the set

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
#pragma omp atomic
            numoutside++;
            break;
        }
    }
}
