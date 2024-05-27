#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
 

int main(int argc, char* argv[])
{
    //double A[1000];
    omp_set_num_threads(4);
    // Beginning of parallel region
    // #pragma omp parallel
    // {
 
        printf("Hello World... from thread = %d\n",omp_get_thread_num());
    //     ID = omp_get_thread_num();
    //     pooh(ID,A);
    // }
    // Ending of parallel region
}