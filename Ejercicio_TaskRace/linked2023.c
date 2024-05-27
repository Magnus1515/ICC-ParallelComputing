#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
    int data;
    int fibdata;
    struct node* next;
};

int fib(int n) {
    int x, y;
    if (n < 2) {
        return (n);
    } else {
        x = fib(n - 1);
        y = fib(n - 2);
        return (x + y);
    }
}

void processwork(struct node* p) {
    int n;
    n = p->data;
    p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;

    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i = 0; i < N; i++) {
        temp = malloc(sizeof(struct node));
        p->next = temp;
        p = temp;
        p->data = FS + i + 1;
        p->fibdata = i + 1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char* argv[]) {
    int num_threads = 8; 
    int num_runs = 5;    

    for (int thread_count = 1; thread_count <= num_threads; thread_count++) {
        double total_avg = 0.0;
        omp_set_num_threads(thread_count);

        for (int run = 0; run < num_runs; run++) {
            double start, end;
            struct node* p = NULL;
            struct node* temp = NULL;
            struct node* head = NULL;

            p = init_list(p);
            head = p;

            start = omp_get_wtime();
            {
                #pragma omp parallel for schedule(auto) // parallel for with static/dynamic/guided/auto
                for (int i = 0; i < N; i++) {
                    #pragma omp task // using the tasks
                    {
                        struct node* local_p = p;
                        for (int j = 0; j < i; j++) {
                            local_p = local_p->next;
                        }
                        processwork(local_p);
                    }
                }
                #pragma omp taskwait // wait for the tasks to complete 
            }
            end = omp_get_wtime();
            total_avg += (end - start);

            p = head;
            while (p != NULL) {
                temp = p->next;
                free(p);
                p = temp;
            }
            free(p);
        }

        double average_time = total_avg / num_runs;
        printf("%f\n", average_time);
    }

    return 0;
}
