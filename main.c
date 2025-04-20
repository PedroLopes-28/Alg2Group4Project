#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "benchmark.h"

int main() {
    int tam, tipoEntrada;
    int* vetorOriginal = NULL;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    if (tam <= 0) {
        printf("Tamanho inválido.\n");
        return 1;
    }

    printf("\nEscolha o tipo de entrada:\n");
    printf("1 - Aleatória\n");
    printf("2 - Quase ordenada\n");
    printf("3 - Ordenada\n");
    printf("Opção: ");
    scanf("%d", &tipoEntrada);

    switch (tipoEntrada) {
        case 1:
            vetorOriginal = geraAleatorios(tam, 42); // semente fixa
            break;
        case 2:
            vetorOriginal = geraQuaseOrdenados(tam, 10); // 10% fora de ordem
            break;
        case 3:
            vetorOriginal = geraOrdenados(tam, 1); // ordem crescente
            break;
        default:
            printf("Opção inválida.\n");
            return 1;
    }

    int* vetTemp;
    int comparacao, troca;
    struct timespec ini, fim;
    long long duracao;

    // Selection Sort
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    selectionSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);
    printf("SelectionSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);
    free(vetTemp);

    // Insertion Sort
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    insertionSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);
    printf("InsertionSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);
    free(vetTemp);

    // Merge Sort
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    mergeSort(vetTemp, 0, tam - 1, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);
    printf("MergeSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);
    free(vetTemp);

    // Quick Sort
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    clock_gettime(CLOCK_MONOTONIC, &ini);
    quickSort(vetTemp, 0, tam - 1, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);
    printf("QuickSort -> Tempo: %lld ns | Comparações: não aplicável | Trocas: não aplicável\n", duracao);
    free(vetTemp);

    // Heap Sort
    vetTemp = malloc(sizeof(int) * (tam + 1)); // +1 porque heap começa em 1
    vetTemp[0] = 0; // não usado, só para ajustar o índice

    // Copia vetorOriginal para vetTemp começando de 1
    for (int i = 0; i < tam; i++) {
        vetTemp[i + 1] = vetorOriginal[i];
    }

    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    heapSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);
    printf("HeapSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);

    free(vetTemp);


    free(vetorOriginal);
    return 0;
}
