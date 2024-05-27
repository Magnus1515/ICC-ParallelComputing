
#include <stdio.h>
#include <omp.h>


int main()
{
  //NECESITAMOS AGREGAR LA REGION PARALELA PARA ELLO NOMAS LA AGREGAMOS 
  #pragma omp parallel
  {
    //AGREGAMOS UN SINGLE PARA QUE SOLO 1 LO CORRA
    #pragma omp single
    {
      printf("A  %d",omp_get_thread_num());
      #pragma omp task
      {printf("race %d",omp_get_thread_num());}
      #pragma omp task
      {printf(" car %d",omp_get_thread_num());}

      // Aparece desaorganizado la frase porque aveces ganan unos threads

      // Para que aparezca al final con el taskwait se espera para ejecutarlo
      
      #pragma omp taskwait
      printf("is fun to watch");
    } 
  }
  printf(" \n");
}
