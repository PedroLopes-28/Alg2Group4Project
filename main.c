#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "benchmark.h"

int main() {
    int tam, tipoEntrada, semente;
    int* vetorOriginal = NULL;

    // Solicita ao usuário o tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    if (tam <= 0) {
        printf("Tamanho inválido.\n");
        return 1;
    }

    // // Menu para o usuário escolher o tipo de entrada
    // printf("\nEscolha o tipo de entrada:\n");
    // printf("1 - Aleatória\n");
    // printf("2 - Quase ordenada\n");
    // printf("3 - Ordenada Crescente\n");
    // printf("4 - Ordenada Decrescente\n");
    // printf("Opção: ");
    // scanf("%d", &tipoEntrada);

    for(tipoEntrada = 0; tipoEntrada < 4; tipoEntrada++){

        // Gera o vetor de acordo com o tipo escolhido
        switch (tipoEntrada) {
            case 0:
                vetorOriginal = geraAleatorios(tam, 42); // Gera vetor aleatório
                printf("\nTipo de Entrada: Vetor Aleatório\n");
                break;
            case 1:
                vetorOriginal = geraQuaseOrdenados(tam, 10, 42); // Vetor quase ordenado
                printf("\nTipo de Entrada: Vetor Quase Ordenado\n");
                break;
            case 2:
                vetorOriginal = geraOrdenados(tam, 0); // Vetor totalmente ordenado crescente
                printf("\nTipo de Entrada: Vetor Ordenado Crescente\n");
                break;
            case 3:
                vetorOriginal = geraOrdenados(tam, 1); // Vetor totalmente ordenado decrescente
                printf("\nTipo de Entrada: Vetor Ordenado Decrescente\n");
                break;
            default:
                printf("Opção inválida.\n");
                return 1;
        }

        int iteracoes;            // Variável para definir quantas iterações serão feitas de cada algoritmo
        int *vetTemp;
        int comparacao, troca;
        struct timespec ini, fim; // Variáveis para medir o tempo
        long long duracao;        // Duração em nanosegundos
        long long media = 0;

        if(tipoEntrada == 0 || tipoEntrada == 1){
            //Se o vetor for aleatório ou quase ordenado, serão feitas cinco iterações para calcular a média entre elas
            iteracoes = 5;
        }else{
            iteracoes = 1;
        }

        // ---------------------- SELECTION SORT ----------------------
        for(int i = 0; i < iteracoes; i++){
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

            if(tipoEntrada == 0 || tipoEntrada == 1){
                media += duracao;
            }

            free(vetTemp);

            if(tipoEntrada == 0){
                free(vetorOriginal);
                vetorOriginal = geraAleatorios(tam, i);
            }else if(tipoEntrada == 1){
                free(vetorOriginal);
                vetorOriginal = geraQuaseOrdenados(tam, 10, i);
            }
        }

        if(tipoEntrada == 0 || tipoEntrada == 1){
            media = media/iteracoes;
            printf("Média de tempo: %lld ns\n", media);
        }

        // ---------------------- INSERTION SORT ----------------------
        for(int i = 0; i < iteracoes; i++){
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

            if(tipoEntrada == 0 || tipoEntrada == 1){
                media += duracao;
            }

            free(vetTemp);
            
            if(tipoEntrada == 0){
                free(vetorOriginal);
                vetorOriginal = geraAleatorios(tam, i);
            }else if(tipoEntrada == 1){
                free(vetorOriginal);
                vetorOriginal = geraQuaseOrdenados(tam, 10, i);
            }
        }

        if(tipoEntrada == 0 || tipoEntrada == 1){
            media = media/iteracoes;
            printf("Média de tempo: %lld ns\n", media);
        }

        // ---------------------- MERGE SORT ----------------------
        for(int i = 0; i < iteracoes; i++){
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

            if(tipoEntrada == 0 || tipoEntrada == 1){
                media += duracao;
            }

            free(vetTemp);
            if(tipoEntrada == 0){
                free(vetorOriginal);
                vetorOriginal = geraAleatorios(tam, i);
            }else if(tipoEntrada == 1){
                free(vetorOriginal);
                vetorOriginal = geraQuaseOrdenados(tam, 10, i);
            }
        }

        if(tipoEntrada == 0 || tipoEntrada == 1){
            media = media/iteracoes;
            printf("Média de tempo: %lld ns\n", media);
        }

        // ---------------------- QUICK SORT ----------------------
        for(int i = 0; i < iteracoes; i++){
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

            if(tipoEntrada == 0 || tipoEntrada == 1){
                media += duracao;
            }

            free(vetTemp);
            if(tipoEntrada == 0){
                free(vetorOriginal);
                vetorOriginal = geraAleatorios(tam, i);
            }else if(tipoEntrada == 1){
                free(vetorOriginal);
                vetorOriginal = geraQuaseOrdenados(tam, 10, i);
            }
        }

        if(tipoEntrada == 0 || tipoEntrada == 1){
            media = media/iteracoes;
            printf("Média de tempo: %lld ns\n", media);
        }

        // ---------------------- HEAP SORT ----------------------
        for(int i = 0; i < iteracoes; i++){
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

            if(tipoEntrada == 0 || tipoEntrada == 1){
                media += duracao;
            }

            free(vetTemp);
            if(tipoEntrada == 0){
                free(vetorOriginal);
                vetorOriginal = geraAleatorios(tam, i);
            }else if(tipoEntrada == 1){
                free(vetorOriginal);
                vetorOriginal = geraQuaseOrdenados(tam, 10, i);
            }
        }

        if(tipoEntrada == 0 || tipoEntrada == 1){
            media = media/iteracoes;
            printf("Média de tempo: %lld ns\n", media);
        }

        // -------------------------------------------------------
        
        // Libera memória alocada do vetor original
        free(vetorOriginal);
    }   

    return 0;
}
