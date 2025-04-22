#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Estrutura para representar um heap (usado no heapSort) */
typedef struct heap heap;

/* Gera um vetor com números aleatórios entre 0 e RANGE */
int* geraAleatorios(int tam, int semente);

/* Gera um vetor ordenado em ordem crescente (ordem = 0) ou decrescente (ordem = 1) */
int* geraOrdenados(int tam, int ordem);

/* Gera um vetor quase ordenado, com base na porcentagem de desordem desejada */
int* geraQuaseOrdenados(int tam, int porcentagem);

/* Ordena o vetor usando o algoritmo Selection Sort e conta comparações e trocas */
void selectionSort(int *vet, int tam, int *comparacao, int *troca);

/* Ordena o vetor usando o algoritmo Insertion Sort e conta comparações e trocas */
void insertionSort(int *vet, int tam, int *comparacao, int *troca);

/* Ordena o vetor usando o algoritmo Merge Sort e conta comparações e trocas */
void mergeSort(int *vet, int inicio, int fim, int *comparacao, int *troca);

/* Função auxiliar do Merge Sort para mesclar duas partes do vetor */
void merge(int *vet, int inicio, int meio, int fim, int *comparacao, int *troca);

/* Ordena o vetor usando o algoritmo Quick Sort e conta comparações e trocas */
void quickSort(int *vet, int inicio, int fim, int *comparacao, int *troca);

/* Função auxiliar do Quick Sort que particiona o vetor */
int particiona(int *vet, int inicio, int fim, int *comparacao, int *troca);

/* Ordena o vetor representado pela struct heap usando Heap Sort */
void heapSort(int *h, int tam, int *comparacao, int *troca);

// Constrói uma heap máxima a partir do vetor
void heapMaximo(int *h, int tam, int *comparacao, int *troca);

/* Função auxiliar do Heap Sort para manter a propriedade do heap */
void heapify(int *h, int tail, int tam, int *comparacao, int *troca);

#endif // BENCHMARK_H
