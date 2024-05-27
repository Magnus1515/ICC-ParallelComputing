

// #include <stdio.h>
// #include <omp.h>
// static long num_steps = 1000000000;
// double step;
// #define PAD 8 
// int total_sum[7][PAD]; 

// int main ()
// {
// 	int i=0;
// 	double pi;
// 	double start_time, run_time;
// 	double final_sum;
// 	step = 1.0/(double) num_steps;
// 	int max_threads = 8;
//     int num_runs = 5;

// 	printf("Thread Count\tAverage Runtime\t\tPi\n");
	
// 	for (int thread_count = 1; thread_count <= max_threads; thread_count++) {
//         double total_avg = 0.0;
//         omp_set_num_threads(thread_count); 
// 		int thread_gl = 0;	
//         for (int run = 0; run < num_runs; run++) {
// 			#pragma omp parallel
// 			{
// 				pi = 0;
// 				int ID = omp_get_thread_num();
// 				int thread = omp_get_num_threads();

// 				if(ID == 0){
// 					thread_gl = thread;
// 				}
// 				start_time = omp_get_wtime();
// 				double sum = 0.0;
// 				int i=0;

// 				for (i = ID ; i <= num_steps; i += thread){
					
// 					double x = (i + 0.5)*step;
// 					sum = sum + 4.0/(1.0+x*x);

// 				}
// 				total_sum[ID][0] = sum;
				
				
// 			}
// 			for(int i=0 ; i < thread_gl; i++){

// 					final_sum += total_sum[i][0];
// 			}
			
// 			run_time = omp_get_wtime() - start_time;

// 			total_avg += run_time;
						
// 			double average_runtime = total_avg / num_runs;
			
// 		}
// 		pi = step * final_sum;
// 		double average_runtime = total_avg / num_runs;
//         printf("%d\t\t%.6lf seconds\t%.6lf\n", thread_count, average_runtime,pi);
// 	}
	
// 	return 0;

 	
// }	  

#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;
double step;
#define PAD 8
int total_sum[PAD * 8];

int main() {
   

	double pi;
    int max_threads = 8;
    int num_runs = 5;
	int thread_gl = 0;

    printf("Thread Count\tAverage Runtime\t\tPi\n");

    for (int thread_count = 1; thread_count <= max_threads; thread_count++) {
        double total_avg = 0.0;
        omp_set_num_threads(thread_count);
		
        for (int run = 0; run < num_runs; run++) {
		

			int i;

			double start_time, run_time;
			double final_sum = 0.0;
			step = 1.0 / (double)num_steps;

            start_time = omp_get_wtime();

			#pragma omp parallel
            {
				int ID = omp_get_thread_num();
				int thread = omp_get_num_threads();
				thread_gl = omp_get_num_threads();
				int thread_gl = thread;

				double sum = 0.0;
                for (i = ID; i <= num_steps; i += thread) {
                    double x = (i + 0.5) * step;
                    sum += 4.0 / (1.0 + x * x);
                }

                total_sum[ID * PAD] = sum;
            }

            
            for (int i = 0; i < thread_gl; i++) {
                final_sum += total_sum[i * PAD];
            }
			pi = step * final_sum;
            run_time = omp_get_wtime() - start_time;
            total_avg += run_time;
        }

        
        double average_runtime = total_avg / num_runs;
        printf("%d\t\t%.6lf seconds\t%.6lf\n", thread_count, average_runtime, pi);
    }

    return 0;
}
