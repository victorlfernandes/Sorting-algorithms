#ifndef _SORT_H_
#define _SORT_H_

typedef int element_t; 

element_t *create_randomized(int n, int lim);
element_t *create_sorted(int n, int lim);
element_t *create_descending(int n, int lim);

void print_array(element_t *array, int n, char *format);

void selection_sort(element_t *array, int n);

void bubble_sort(element_t *array, int n);
void bubble_sort_rec(element_t *array, int n, int i);

void insertion_sort(element_t *array, int n);
void insertion_sort_rec(element_t *array, int n, int i);

void merge_sort(element_t *array, int start, int end);

void quick_sort(element_t *array, int start, int end, int (*pivot)() );
int random_pivot(int start, int end);
int start_pivot(int start);
int central_pivot(int start, int end);

void heap_sort(element_t *array, int n);

void counting_sort(element_t *array, int n);

#endif