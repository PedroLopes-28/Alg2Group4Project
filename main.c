#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "benchmark.h"

int main() {
    int tam, tipoEntrada;
    int* vetorOriginal = NULL;

    // Solicita ao usuário o tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    if (tam <= 0) {
        printf("Tamanho inválido.\n");
        return 1;
    }

    // Menu para o usuário escolher o tipo de entrada
    printf("\nEscolha o tipo de entrada:\n");
    printf("1 - Aleatória\n");
    printf("2 - Quase ordenada\n");
    printf("3 - Ordenada\n");
    printf("Opção: ");
    scanf("%d", &tipoEntrada);

    // Gera o vetor de acordo com o tipo escolhido
    switch (tipoEntrada) {
        case 1:
            vetorOriginal = geraAleatorios(tam, 42); // Gera vetor aleatório
            break;
        case 2:
            vetorOriginal = geraQuaseOrdenados(tam, 10); // Vetor quase ordenado
            break;
        case 3:
            vetorOriginal = geraOrdenados(tam, 0); // Vetor totalmente ordenado
            break;
        default:
            printf("Opção inválida.\n");
            return 1;
    }

    int *vetTemp;
    int comparacao, troca;
    struct timespec ini, fim; // Variáveis para medir o tempo
    long long duracao;        // Duração em nanosegundos

    // ---------------------- SELECTION SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam); // Copia vetor original para vetTemp
    comparacao = troca = 0;


    clock_gettime(CLOCK_MONOTONIC, &ini);//pega o tempo antes de iniciar a função de ordenação
    selectionSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);//pega o tempo após de iniciar a função de ordenação


    // Cálculo da duração
    //(fim.tv_sec - ini.tv_sec) * 1000000000LL converte o tempo inteiro em segundos para o tempo fracionário em nanosegundos
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);

    // Imprime estatísticas
    printf("SelectionSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- INSERTION SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;


    clock_gettime(CLOCK_MONOTONIC, &ini);//pega o tempo antes de iniciar a função de ordenação
    insertionSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);//pega o tempo após de iniciar a função de ordenação

    // Cálculo da duração
    //(fim.tv_sec - ini.tv_sec) * 1000000000LL converte o tempo inteiro em segundos para o tempo fracionário em nanosegundos
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);

    printf("InsertionSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- MERGE SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;


    clock_gettime(CLOCK_MONOTONIC, &ini);//pega o tempo antes de iniciar a função de ordenação
    mergeSort(vetTemp, 0, tam - 1, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);//pega o tempo após de iniciar a função de ordenação

    // Cálculo da duração
    //(fim.tv_sec - ini.tv_sec) * 1000000000LL converte o tempo inteiro em segundos para o tempo fracionário em nanosegundos
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);

    printf("MergeSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- QUICK SORT ----------------------
    vetTemp = malloc(sizeof(int) * tam);
    memcpy(vetTemp, vetorOriginal, sizeof(int) * tam);
    comparacao = troca = 0;


    clock_gettime(CLOCK_MONOTONIC, &ini);//pega o tempo antes de iniciar a função de ordenação
    quickSort(vetTemp, 0, tam - 1, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);//pega o tempo após de iniciar a função de ordenação

    // Cálculo da duração
    //(fim.tv_sec - ini.tv_sec) * 1000000000LL converte o tempo inteiro em segundos para o tempo fracionário em nanosegundos
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);

    printf("QuickSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);
    free(vetTemp);

    // ---------------------- HEAP SORT ----------------------
    // Aqui, o vetor precisa começar do índice 1
    vetTemp = malloc(sizeof(int) * (tam + 1));
    vetTemp[0] = 0; // índice 0 não utilizado

    // Copia elementos do vetor original para vetTemp, começando da posição 1
    for (int i = 0; i < tam; i++) {
        vetTemp[i + 1] = vetorOriginal[i];
    }
    comparacao = troca = 0;


    clock_gettime(CLOCK_MONOTONIC, &ini);//pega o tempo antes de iniciar a função de ordenação
    heapSort(vetTemp, tam, &comparacao, &troca);
    clock_gettime(CLOCK_MONOTONIC, &fim);//pega o tempo após de iniciar a função de ordenação

    // Cálculo da duração
    //(fim.tv_sec - ini.tv_sec) * 1000000000LL converte o tempo inteiro em segundos para o tempo fracionário em nanosegundos
    duracao = (fim.tv_sec - ini.tv_sec) * 1000000000LL + (fim.tv_nsec - ini.tv_nsec);

    printf("HeapSort -> Tempo: %lld ns | Comparações: %d | Trocas: %d\n", duracao, comparacao, troca);
    free(vetTemp);

    // -------------------------------------------------------

    // Libera memória alocada do vetor original
    free(vetorOriginal);

    return 0;
}
