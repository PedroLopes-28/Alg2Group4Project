#include <stdio.h>      // Entrada e saída padrão
#include <stdlib.h>     // Alocação dinâmica e funções auxiliares
#include <string.h>     // Função memcpy
#include <time.h>       // Medição de tempo com clock_gettime
#include "benchmark.h"  // Header com protótipos e definições do benchmark

int main() {
    int tam, tipoEntrada;      // Tamanho do vetor e tipo de entrada escolhido pelo usuário
    int* vetorOriginal = NULL; // Ponteiro para armazenar o vetor base (não modificado)

    // Solicita o tamanho do vetor ao usuário
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    // Verifica se o tamanho é válido
    if (tam <= 0) {
        printf("Tamanho inválido.\n");
        return 1;
    }

    // Menu de tipo de entrada para o vetor
    printf("\nEscolha o tipo de entrada:\n");
    printf("1 - Aleatória\n");
    printf("2 - Quase ordenada\n");
    printf("3 - Ordenada crescente\n");
    printf("4 - Ordenada decrescente\n");
    printf("Opção: ");
    scanf("%d", &tipoEntrada);

    // Gera o vetor com base na escolha do usuário
    switch (tipoEntrada) {
        case 1:
            vetorOriginal = geraAleatorios(tam, SEED); // Vetor com números aleatórios
            break;
        case 2:
            vetorOriginal = geraQuaseOrdenados(tam, 10); // 10% fora de ordem
            break;
        case 3:
            vetorOriginal = geraOrdenados(tam, 0); // Ordenado crescente
            break;
        case 4:
            vetorOriginal = geraOrdenados(tam, 1); // Ordenado decrescente
            break;
        default:
            printf("Opção inválida.\n");
            return 1;
    }

    int *vetTemp;                      // Vetor temporário para cópia e ordenação
    int comparacao, troca;            // Contadores de comparações e trocas
    struct timespec ini, fim;         // Estruturas para marcação de tempo
    long long duracao;                // Duração da execução em nanosegundos

    // ---------------------- SELECTION SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);                        // Aloca vetor temporário
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);         // Copia dados do vetor original
    comparacao = troca = 0;                                    // Zera contadores
    clock_gettime(CLOCK_MONOTONIC, &ini);                      // Marca início
    selectionSort(vetTemp, tam, &comparacao, &troca);          // Executa o algoritmo
    clock_gettime(CLOCK_MONOTONIC, &fim);                      // Marca fim
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL +       // Calcula duração em ns
              (fim.tv_nsec - ini.tv_nsec);
    printf("SelectionSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n",
           duracao, comparacao, troca);
    free(vetTemp);                                             // Libera memória

    // ---------------------- INSERTION SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    insertionSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL +
              (fim.tv_nsec - ini.tv_nsec);
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
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL +
              (fim.tv_nsec - ini.tv_nsec);
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
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL +
              (fim.tv_nsec - ini.tv_nsec);
    printf("QuickSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n",
           duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- HEAP SORT ----------------------
    heap h;
    h.vet = malloc(sizeof(int) * tam);                         // Aloca vetor dentro da struct heap
    memcpy(h.vet, vetorOriginal, sizeof(int) * tam);           // Copia dados
    h.tam = tam;
    comparacao = troca = 0;
    clock_gettime(CLOCK_MONOTONIC, &ini);
    heapSort(&h, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL +
              (fim.tv_nsec - ini.tv_nsec);
    printf("HeapSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n",
           duracao, comparacao, troca);
    free(h.vet);

    // Libera o vetor original
    free(vetorOriginal);

    return 0;
}