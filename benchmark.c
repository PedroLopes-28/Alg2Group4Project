
#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>

struct heap;

//gera um vetor de int com numeros aleatórios
int* geraAleatorios(int tam, int semente);

//gera um vetor de int com numeros quase ordenados
int* geraQuaseOrdenados(int tam, int porcentagem);

//gera um vetor com os dados ordenados
int* geraOrdenados(int tam, int ordem);

//usa o método selectionSort para ordenar o vetor
void selectionSort(int *vet, int tam, int *comparacao, int *troca);

//usa o método insertionSort para ordenar o vetor
void insertionSort(int* vet, int tam, int *comparacao, int *troca);

//usa o método mergeSort para ordenar o vetor
void mergeSort(int *vet, int inicio, int fim);
void merge(int *vet, int inicio, int meio, int fim, int *comparacao, int *troca);

//usa o método quicksort para ordenar o vetor
void quickSort(int *vet, int inicio, int fim);
int particiona(int *vet, int inicio, int fim,int *comparacao, int *troca);

//usa o método de heapSort para ordenar o vetor
void heapSort(heap *h,int *comparacao, int *troca);
void heapify(heap *h, int atual,int *comparacao, int *troca);
