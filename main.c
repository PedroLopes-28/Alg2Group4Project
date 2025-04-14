#include <stdio.h>      // Entrada e saída padrão (printf, scanf)
#include <stdlib.h>     // malloc, free, exit
#include <string.h>     // memcpy
#include <time.h>       // clock_gettime, struct timespec
#include "benchmark.h"  // Header com protótipos das funções e struct heap

// Função auxiliar para calcular o tempo em nanosegundos com verificação robusta
long long calculaTempo(struct timespec ini, struct timespec fim) {
    if (fim.tv_nsec < ini.tv_nsec) {
        fim.tv_sec--;
        fim.tv_nsec += 1000000000;
    }
    return (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);
}

int main() {
    int tam, tipoEntrada;
    int* vetorOriginal = NULL;

    // Solicita o tamanho do vetor ao usuário
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    // Valida o tamanho
    if (tam <= 0) {
        printf("Tamanho inválido.\n");
        return 1;
    }

    // Menu para escolha do tipo de entrada
    printf("\nEscolha o tipo de entrada:\n");
    printf("1 - Aleatória\n");
    printf("2 - Quase ordenada\n");
    printf("3 - Ordenada crescente\n");
    printf("4 - Ordenada decrescente\n");
    printf("Opção: ");
    scanf("%d", &tipoEntrada);

    // Geração do vetor conforme o tipo escolhido
    switch (tipoEntrada) {
        case 1:
            vetorOriginal = geraAleatorios(tam, SEED);
            break;
        case 2:
            vetorOriginal = geraQuaseOrdenados(tam, 10);
            break;
        case 3:
            vetorOriginal = geraOrdenados(tam, 0);
            break;
        case 4:
            vetorOriginal = geraOrdenados(tam, 1);
            break;
        default:
            printf("Opção inválida.\n");
            return 1;
    }

    int *vetTemp;
    int comparacao, troca;
    struct timespec ini, fim;
    long long duracao;

    // ---------------------- SELECTION SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    selectionSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = calculaTempo(ini, fim);
    printf("SelectionSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n",
           duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- INSERTION SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    insertionSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = calculaTempo(ini, fim);
    printf("InsertionSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n",
           duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- MERGE SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    mergeSort(vetTemp, 0, tam - 1, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = calculaTempo(ini, fim);
    printf("MergeSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n",
           duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- QUICK SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    quickSort(vetTemp, 0, tam - 1, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = calculaTempo(ini, fim);
    printf("QuickSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n",
           duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- HEAP SORT ----------------------
    heap h;
    h.vet = malloc(sizeof(int) * tam);
    memcpy(h.vet, vetorOriginal, sizeof(int) * tam);
    h.tam = tam;
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    heapSort(&h, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = calculaTempo(ini, fim);
    printf("HeapSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n",
           duracao, comparacao, troca);
    free(h.vet);

    // Libera o vetor original
    free(vetorOriginal);

    return 0;
}
