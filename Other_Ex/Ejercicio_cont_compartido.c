#include <stdio.h>
#include <omp.h>

int main ()
{
	
	int sharedCounter = 0;
	int numIncrements =1000000;
	int numThreads = omp_get_max_threads();
	
	 #pragma omp parallel num_threads(numThreads)
    {
	
		for (int i = 0 ; i <= numIncrements; i ++){
			#pragma omp critical
            	sharedCounter ++;

		}		
	}
	
	printf("Valor final de sharedCounter %d\n",sharedCounter);

	return 0;

}	  




