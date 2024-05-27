#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

int counter = 0;

struct node
{
   int data;
   int fibdata;
   struct node *next;
};

int fib(int n)
{
   int x, y;
   if (n < 2)
   {
      return (n);
   }
   else
   {
      x = fib(n - 1);
      y = fib(n - 2);
      return (x + y);
   }
}

void processwork(struct node *p)
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node *init_list(struct node *p)
{
   int i;
   struct node *head = NULL;
   struct node *temp = NULL;
   int x;
   head = malloc(sizeof(struct node));
   p = head;
   p->data = FS;
   p->fibdata = 0;

   for (i = 0; i < N; i++)
   {
      temp = malloc(sizeof(struct node));
      p->next = temp;
      p = temp;
      p->data = FS + i + 1;
      p->fibdata = i + 1; // El apuntador al arreglo, el apuntador que salga de aqui lo guardar
      // PointerToA = &p;
   }
   // Necesitamos saber hasta donde termina mi lista ligara
   //
   // for(int j=0; j < N; j++){
   p->next = NULL;

   return head;
}

int main(int argc, char *argv[])
{

   double start, end;
   struct node *p = NULL;
   struct node *temp = NULL;
   struct node *head = NULL;
   struct node *PointerTo = NULL;

   printf("Process linked list\n");
   printf("  Each linked list node will be processed by function 'processwork()'\n");
   printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n", N, FS);

   p = init_list(p);
   head = p;

   // Se necesitara mover la estructura de datos
   // para el procesamiento
   start = omp_get_wtime();
   {
      // NECESITAMOS INDICAR HASTA DONDE TERMINIARA

      while (p != NULL)
      {
         // processwork(p);
         p = p->next;
         counter++;
      }
      // un array de pointer, un apuntador que apunte a un arreglo de apuntadores
      // con el apuntador

      //  En ese for le vamos a meter cada pointer en el array

      // ese for si lo vamos a mandar en el parallel
      struct node *array_of_pointers[10];
      PointerTo = head;
      for (int j = 0; j < counter; j++)
      {
         array_of_pointers[j] = PointerTo;
         PointerTo = PointerTo->next;
      }
      // Crear un array del tamaño de cuantos nodos tenemos
      omp_set_num_threads(1);
      #pragma omp parallel for
      for (int i = 0; i < counter; i++)
      {
         // Ejecutamos nuestro array_of_pointer en cada una de las posiciones
         processwork(array_of_pointers[i]);
      }
   }

   end = omp_get_wtime();
   p = head;
   while (p != NULL)
   {
      printf("%d : %d\n", p->data, p->fibdata);
      temp = p->next;
      free(p);
      p = temp;
   }
   free(p);

   printf("Compute Time: %f seconds\n", end - start);

   return 0;
}