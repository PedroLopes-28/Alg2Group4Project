#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "benchmark.h"

int main() {
    int tam, tipoEntrada, semente;
    int* vetorOriginal = NULL;
    const char* nomesAlgoritmos[] = {"Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort", "Heap Sort"};

    // Solicita ao usuário o tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);

    if (tam <= 0) {
        printf("Tamanho inválido.\n");
        return 1;
    }

    for(tipoEntrada = 0; tipoEntrada < 4; tipoEntrada++){
    //Laço for para repetir os testes por cada tipo de entrada

        // Gera o vetor de acordo com o tipo de entrada
        switch (tipoEntrada) {
            case 0: // Vetor com elementos gerados aleatoriamente
                printf("\n------------------------------------------------------------\n");
                printf("Tipo de Entrada: Vetor Aleatório\n");
                printf("------------------------------------------------------------\n\n");
                break;
            case 1: // Vetor com alguns elementos desordenados
                srand(time(NULL));
                printf("\n------------------------------------------------------------\n");
                printf("Tipo de Entrada: Vetor Quase Ordenado\n");
                printf("------------------------------------------------------------\n\n");
                break;
            case 2:
                vetorOriginal = geraOrdenados(tam, 0); // Vetor totalmente ordenado crescente
                printf("\n------------------------------------------------------------\n");
                printf("Tipo de Entrada: Vetor Ordenado Crescente\n");
                printf("------------------------------------------------------------\n\n");
                break;
            case 3:
                vetorOriginal = geraOrdenados(tam, 1); // Vetor totalmente ordenado decrescente
                printf("\n------------------------------------------------------------\n");
                printf("Tipo de Entrada: Vetor Ordenado Decrescente\n");
                printf("------------------------------------------------------------\n\n");
                break;
            default:
                printf("Opção inválida.\n");
                return 1;
        }

        int iteracoes;            // Variável para definir quantas iterações serão feitas de cada algoritmo
        int *vetTemp;
        long long comparacao, troca;
        struct timespec ini, fim; // Variáveis para medir o tempo
        long long duracao;        // Duração em nanosegundos
        long long mediaTempo[5] = {0}; // Vetor para armazenar as médias de tempo, cada posição é referente a um algoritmo
        long long mediaComparacoes[5] = {0}; // Vetor para armazenar as médias de comparacoes, cada posição é referente a um algoritmo
        long long mediaTrocas[5] = {0}; // Vetor para armazenar as médias de trocas, cada posição é referente a um algoritmo

        if(tipoEntrada == 0 || tipoEntrada == 1){
            //Se o vetor for aleatório ou quase ordenado, serão feitas cinco iterações para calcular a média entre elas
            iteracoes = 5;
        }else{
            iteracoes = 1;
        }
 
        printf("Algoritmo        | Tempo (ns)         | Comparações   | Trocas   \n");
        printf("---------------------------------------------------------------------\n");

        // ---------------------- SELECTION SORT ----------------------
        for(int i = 0; i < iteracoes; i++){
            if(tipoEntrada == 0){
                vetorOriginal = geraAleatorios(tam, i);
            }else if(tipoEntrada == 1){
                vetorOriginal = geraQuaseOrdenados(tam, 10);
            }

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
            // printf("SelectionSort -> Tempo: %lld ns | Comparações: %lld | Trocas: %lld\n", duracao, comparacao, troca);
            printf("%-16s | %15lld ns | %15lld | %10lld\n", "Selection Sort", duracao, comparacao, troca);

            if(tipoEntrada == 0 || tipoEntrada == 1){
                // Adiciona os valores na posição indicada na média, para cálculo posterior
                mediaTempo[0] += duracao;
                mediaComparacoes[0] += comparacao;
                mediaTrocas[0] += troca;
            }

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

            // printf("InsertionSort -> Tempo: %lld ns | Comparações: %lld | Trocas: %lld\n", duracao, comparacao, troca);
            printf("%-16s | %15lld ns | %15lld | %10lld\n", "Insertion Sort", duracao, comparacao, troca);

            if(tipoEntrada == 0 || tipoEntrada == 1){
                // Adiciona os valores na posição indicada na média, para cálculo posterior
                mediaTempo[1] += duracao;
                mediaComparacoes[1] += comparacao;
                mediaTrocas[1] += troca;
            }

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

            // printf("MergeSort -> Tempo: %lld ns | Comparações: %lld | Trocas: %lld\n", duracao, comparacao, troca);
            printf("%-16s | %15lld ns | %15lld | %10lld\n", "Merge Sort", duracao, comparacao, troca);

            if(tipoEntrada == 0 || tipoEntrada == 1){
                // Adiciona os valores na posição indicada na média, para cálculo posterior
                mediaTempo[2] += duracao;
                mediaComparacoes[2] += comparacao;
                mediaTrocas[2] += troca;
            }

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

            // printf("QuickSort -> Tempo: %lld ns | Comparações: %lld | Trocas: %lld\n", duracao, comparacao, troca);
            printf("%-16s | %15lld ns | %15lld | %10lld\n", "Quick Sort", duracao, comparacao, troca);

            if(tipoEntrada == 0 || tipoEntrada == 1){
                // Adiciona os valores na posição indicada na média, para cálculo posterior
                mediaTempo[3] += duracao;
                mediaComparacoes[3] += comparacao;
                mediaTrocas[3] += troca;
            }

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

            // printf("HeapSort -> Tempo: %lld ns | Comparações: %lld | Trocas: %lld\n", duracao, comparacao, troca);
            printf("%-16s | %15lld ns | %15lld | %10lld\n", "Heap Sort", duracao, comparacao, troca);

            if(tipoEntrada == 0 || tipoEntrada == 1){
                // Adiciona os valores na posição indicada na média, para cálculo posterior
                mediaTempo[4] += duracao;
                mediaComparacoes[4] += comparacao;
                mediaTrocas[4] += troca;
            }

            free(vetTemp);
        
            // Libera memória alocada do vetor original
            free(vetorOriginal);

            printf("\n");
        }

        if(tipoEntrada == 0 || tipoEntrada == 1){
            // Calcula a média, caso o tipo de entrada seja Aleatória ou Quase Ordenada
            for(int i = 0; i < 5; i++){
                // A média é a soma total pelo número de iterações
                mediaTempo[i] = mediaTempo[i]/iteracoes;
                mediaComparacoes[i] = mediaComparacoes[i]/iteracoes;
                mediaTrocas[i] = mediaTrocas[i]/iteracoes;
            }
            // printf("Média de tempo do Selection Sort: %lld ns\n", media[0]);
            // printf("Média de tempo do Insertion Sort: %lld ns\n", media[1]);
            // printf("Média de tempo do Merge Sort: %lld ns\n", media[2]);
            // printf("Média de tempo do Quick Sort: %lld ns\n", media[3]);
            // printf("Média de tempo do Heap Sort: %lld ns\n", media[4]);
            printf("---------------------------------------------------------------------------------\n");
            printf("Algoritmo        | Tempo médio (ns) | Comparações médias | Trocas médias\n");
            printf("---------------------------------------------------------------------------------\n");
            for (int i = 0; i < 5; i++) {
                printf("%-16s | %17lld | %21lld | %16lld\n", nomesAlgoritmos[i], mediaTempo[i], mediaComparacoes[i], mediaTrocas[i]);
            }
            printf("---------------------------------------------------------------------------------\n");
        }
    }   

    return 0;
}
