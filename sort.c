#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

element_t *create_randomized(int n, int lim) {

    element_t *array = malloc(n * sizeof(element_t));
    srand(time(NULL));

    for (int i = 0; i < n; i++) 
        array[i] = rand() % lim;

    return array;
}

element_t *create_sorted(int n, int lim) {

    element_t *array = malloc(n * sizeof(element_t));
    srand(time(NULL));

    int nxt = 0;
    for (int i = 0; i < n; i++) {
        array[i] = nxt;
        nxt = array[i] + (rand() % 3) + 1;
        if (nxt > lim)
            nxt = lim;
    }

    return array;
}

element_t *create_descending(int n, int lim) {

    element_t *array = malloc(n * sizeof(element_t));
    
    srand(time(NULL));
    int cte = rand() % lim + 1;

    for (int i = 0; i < n; i++) 
        array[i] = (cte * lim) - (i * lim) + lim;

    return array;
}

void print_array(element_t *array, int n, char *format) {

    for (int i = 0; i < n; i++) 
        printf(format, array[i]);
    
    printf("\n");
}

void selection_sort(element_t *array, int n) {

    for (int i = n; i > 0; i--) {
        
        element_t largest = array[0];
        int pos_largest = 0;
        
        for (int j = 1; j <= i; j++) {
            if (array[j] > largest) {
                largest = array[j];
                pos_largest = j;
            }
        }

        array[pos_largest] = array[i];
        array[i] = largest;
    }
}

void bubble_sort(element_t *array, int n) {
    
    // variável responsável por interromper a iteração caso não ocorra troca, 
    // pois já estamos com o valor na posição correta
    bool swap = false;

		// vamos até n - 1 pois precisamos comparar com todos os elementos, 
		// desconsiderando apenas o atual
    for (int i = 0; i < n - 1; i++) {

        // vamos até n - i - 1 porque a cada vez que percorremos o vetor,
        // a última posição é preenchida com o valor correto, e não precisamos 
        // iterar sobre ela novamente
        for (int j = 0; j < n - i - 1; j++) {

            if (array[j] > array[j + 1]) {

                int aux      = array[j];
                array[j]     = array[j + 1];
                array[j + 1] = aux;
                swap         = true;

            }
        }            
        
        if (!swap) break;
    }
}

void bubble_sort_rec(element_t *array, int n, int i) {
    
    if (i >= (n - 1)) return;
    
    bool swap = false;

    for (int j = 0; j < n - i - 1; j++) {

        if (array[j] > array[j + 1]) {

            int aux      = array[j];
            array[j]     = array[j + 1];
            array[j + 1] = aux;
            swap         = true;

        }

    }
        
    if (!swap) return;
    bubble_sort_rec(array, n, i + i);
}

void insertion_sort(element_t *array, int n) {

	int i = 1;
	while (i < n) {
	
    	int key = array[i];
		int j = i - 1;
	
    	while (j >= 0 && key < array[j]) {
			array[j + 1] = array[j];
			j--;
		}
	
    	array[j + 1] = key;
		i++;
	}
}

void insertion_sort_rec(element_t *array, int n, int i) {
    
    if (i >= n) return;
    
    int key = array[i];
    int j = i - 1;
    
    while (j >= 0 && key < array[j]) {
        array[j + 1] = array[j];
        j--;
    
    }

    array[j + 1] = key;
    i++;
    
    insertion_sort_rec(array, n, i);
}

void merge_sort(element_t *array, int start, int end) {
    
    // condição de parada da divisão, vetor tem tamanho 1
    if (start >= end) return;

    // cálculo do centro do vetor
    int center = (int) (start + end) / 2.0;

    // passo recursivo da divisão
    merge_sort(array, start, center); // primeira metade
    merge_sort(array, center + 1, end); // segunda metade

    // ao chegarmos aqui, temos a garantia de dois vetores ordenados
    
    // criando vetor auxiliar
    element_t *aux_array = malloc((end - start + 1) * sizeof(int));

    // índices para intercalar
    int i = start; // para o primeiro vetor, vai até o centro
    int j = center + 1; // para o segundo vetor, vai até o fim
    int k = 0; // para o vetor auxiliar, vai até fim - início

    // enquanto os dois vetores tiverem elementos, vejo quem tem o menor valor
    while (i <= center && j <= end) {
        if (array[i] <= array[j]) {
            aux_array[k] = array[i];
            i++;
        }
        else {
            aux_array[k] = array[j];
            j++;
        }
        k++;
    }

    // ao chegarmos aqui, um dos dois vetores está vazio. basta copiar o restante
    // do outro vetor para o auxiliar. como não sabemos qual é ele, fazemos o
    // while para os dois, mas ele só entra em um 
    while (i <= center) {
        aux_array[k] = array[i];
        i++; k++;
    }
    while (j <= end) {
        aux_array[k] = array[j];
        j++; k++;
    }

    // agora precisamos copiar o vetor auxiliar ordenado para o vetor original
    for (i = start, k = 0; i <= end; i++, k++)
        array[i] = aux_array[k];

    free(aux_array);
}

void quick_sort(element_t *array, int start, int end, int (*pivot)() ) {
    
    if (start >= end) return;

    int p = pivot(start, end);
    
    int aux = array[p];
    array[p] = array[start];
    array[start] = aux;

    p = start;
    int i = start + 1; 
    int j = end;       

    while (i <= j) {

        while (i <= end && array[i] <= array[p]) i++;
        while (array[j] > array[p]) j--;
        if (i < j) {
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
        }

    }

    aux = array[p];
    array[p] = array[j];
    array[j] = aux;
    p = j;
    
    quick_sort(array, start, p - 1, pivot);
    quick_sort(array, p + 1, end, pivot);
}

// caso patologico = pivo aleatorio, valor próximo do minimo ou maximo
// esse caso existe, mas é muito difícil de ser escolhido
int random_pivot(int start, int end) {
	return (int)(rand()%(end - start)) + start; 
}

// caso patologico = ordenado
int start_pivot(int start) {
	return start; 
}

// caso patologico = ordenado até o centro e depois ordenado de forma invertida
// 0 1 5 6 9 4 2 1 0
// 9 7 4 3 1 2 5 8 9
int central_pivot(int start, int end) {
	return (int) ((start + end) / 2.0); 
}

void max_heapify(element_t *array, int n, int pos) {

    // variável para guardar a posição do maior filho
    // começamos assumindo que o maior é o da esquerda
    int child = 2 * pos;

    // verifica se o filho da esquerda existe, ou seja,
    // se a posição dele é menor do que o tamanho do vetor
    if (child < n) {

        // verifica se o filho da direita existe, e caso existir,
        // se é maior do que o da esquerda
        if (child + 1 < n && array[child + 1] > array[child])
            // atualiza o maior filho como o da direita
            child++;

        // agora que achamos o maior filho, precisamos saber se
        // ele é maior do que o pai
        if (array[child] > array[pos]) {

            // trocamos o filho com o pai
            element_t aux = array[pos];
            array[pos] = array[child];
            array[child] = aux;

            // sempre que fazemos uma troca, precisamos verificar
            // se ela quebra as regras do max heap para os nós
            // inferiores ao filho trocado
            // para isso, fazemos uma chamada recursiva para o filho
            max_heapify(array, n, child);
        }
    }
}

void build_maxheap(element_t *array, int n) {

    // encontrando o último nó que tem filho
    int last_root = (int) n / 2.0;

    // garantindo que toda a árvore está em max heap
    // ou seja, começa no último nó que tem filho e percorre
    // todos os outros pais garantindo que os filhos são menores
    for (int i = last_root; i >=1; i--)
        max_heapify(array, n, i);

}

void heap_sort(element_t *array, int n) {

    // transformando a árvore em max heap
    build_maxheap(array, n);

    // cada iteração do while é responsável por colocar na posição correta
    // o maior elemento que ainda não foi ordenado, que, pelo max heap,
    // está na raiz da árvore
    // como cada iteração resolve um elemento, precisamos iterar n vezes
    while (n >= 1) {

        // trocando a raiz da árvore (maior elemento) com o último nó
        element_t largest = array[1];
        array[1] = array[n];
        array[n] = largest;

        // como resolvemos um elemento, diminuímos em 1 o tamanho do vetor
        n--;

        // achando a posição correta do elemento que trocou com o maior,
        // que agora ocupa a raiz da árvore
        max_heapify(array, n, 1);
    }
}

void counting_sort(element_t *array, int n) {

    // achando o menor e o maior valor do vetor
    int min = array[0];
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] < min) min = array[i];
        if (array[i] > max) max = array[i];
    }

    // criando o vetor de contagem
    int counter_s = max - min + 1;
    int *counter = calloc(counter_s, sizeof(int));

    // contando a frequência de cada chave
    for (int i = 0; i < n; i++) {
        // subtraímos min para tratar o caso das chaves não começarem em 0
        int pos = array[i] - min;
        counter[pos]++;
    }

    // retornando os valores contados para o vetor original
    int i = 0;
    // percorremos todas as posições da contagem
    for (int j = 0; j < counter_s; j++) {
        // até que o valor da contagem seja nulo
        while (counter[j] > 0) {
            // como subtraímos min, precisamos somar para voltar o valor
            array[i] = j + min;
            counter[j]--;
            i++;
        }
    }

    free(counter);
}

typedef struct data {
    int key;
    char ch;
} data_t;

void countingsort(data_t *array, int n) {

    data_t *copy = malloc(n * sizeof(data_t));

    int min = array[0].key;
    int max = array[0].key;
    for (int i = 1; i < n; i++) {
        if (array[i].key < min) min = array[i].key;
        if (array[i].key > max) max = array[i].key;
        copy[i] = array[i];
    }

    int counter_s = max - min + 1;
    int *counter = calloc(counter_s, sizeof(int));

    for (int i = 0; i < n; i++) {
        int pos = array[i].key - min;
        counter[pos]++;
    }

    int total = 0;
    for (int j = 0; j < counter_s; j++) {
        int aux = counter[j];
        counter[j] = total;
        total += aux;
    }
    
    for (int i = 0; i < n; i++) {
        int pos = counter[copy[i].key - min];
        array[pos] = copy[pos];
        counter[copy[i].key - min]++;
    }

    free(copy);
    free(counter);
}