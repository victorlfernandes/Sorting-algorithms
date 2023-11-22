#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Missing arguments\n");
        return EXIT_FAILURE;
    }

    int n   = atoi(argv[1]);
    int lim = atoi(argv[2]);
    
    int prt = 0;
    if (n < 20)
        prt = 1;

    /*
    element_t *array = create_sorted(n, lim);
    element_t *array = create_descending(n, lim);
    array[0] = -1; // para o heap sort
    */
    element_t *array = create_randomized(n, lim);

    if (prt)
        print_array(array, n, "%d ");
    
    clock_t c1 = clock();
    
    /*
    bubble_sort(array, n);
    selection_sort(array, n - 1);
    insertion_sort(array, n);
    heap_sort(array, n - 1);
    quick_sort(array, 0, n - 1, random_pivot);
    merge_sort(array, 0, n - 1);
    */
   counting_sort(array, n);

    clock_t c2 = clock();
    double time = (c2 - c1) / (double) CLOCKS_PER_SEC;
    
    if (prt)
        print_array(array, n, "%d ");
    
    printf("%lf\n", time); 

    free(array); 
    return EXIT_SUCCESS;
}