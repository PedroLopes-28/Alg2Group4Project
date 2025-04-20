
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "benchmark.h"

/* Estrutura para representar um heap (usado no heapSort) */
struct heap {
    int *vet;  // Vetor que representa o heap
    int tam;   // Tamanho atual do heap
};


/* Gera um vetor com números aleatórios entre 0 e RANGE */
int* geraAleatorios(int tam, int semente){
    //Inicializa a semente geradora de números
    srand(semente);

    //Alocação de memória
    int *vet = (int*) malloc(tam * sizeof(int));
    if (vet == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

   //Preenche o vetor com números aleatórios entre 0 e 999
    for(int i = 0; i < tam; i++){
        vet[i] = rand() % (1000);
    }

    return vet;
};

/* Gera um vetor quase ordenado, com base na porcentagem de desordem desejada */
int* geraQuaseOrdenados(int tam, int porcentagem){
//Define o número de trocas a serem feitas baseada na porcentagem indicada
int numTrocas = (int)(tam * porcentagem / 100);

//Inicializa a semente geradora de números com um valor padrão
srand(2);

//Gera vetor ordenado
int* vet = geraOrdenados(tam, 0);

//Faz trocas aleatórias
for(int i = 0; i<numTrocas; i++){
    int a = rand() % tam;
    int b = rand() % tam;
    if(a != b){
        int aux = vet[a];
        vet[a] = vet[b];
        vet[b] = aux;
    }
}

return vet;
};

/* Gera um vetor ordenado em ordem crescente (ordem = 0) ou decrescente (ordem = 1) */
int* geraOrdenados(int tam, int ordem){
//Alocação de memória
int *vet = (int*) malloc(tam * sizeof(int));
if (vet == NULL) {
    printf("Erro ao alocar memória!\n");
    return NULL;
}

//Preenche o vetor com números
for(int i=0; i<tam; i++){
    if(ordem == 0){
        //Adiciona números em ordem crescente
        vet[i] = i;
    }else{
        //Adiciona números em ordem decrescente
        vet[i] = tam-i-1;
    }
}

return vet;
};

/* Ordena o vetor usando o algoritmo Selection Sort e conta comparações e trocas */
void selectionSort(int *vet, int tam, int *comparacao, int *troca){
    int marcador = 0;
    int menor = 0;
    int aux;

    while(marcador < tam-1){
        //Define o menor elemento como o primeiro elemento após o marcador
        menor = marcador+1;

        //Encontra o menor elemento do vetor desordenado
        for(int i=marcador+1; i<tam; i++){
            //Aumenta o número de comparações a cada iteração
            (*comparacao)++;
            if(vet[menor] > vet[i]){
                menor = i;
            }
        }

        //Se o menor elemento do vetor desordenado for menor do que o elemento no marcador, troca a posição deles
        if(vet[menor] < vet[marcador]){
            (*troca)++;
            aux = vet[marcador];
            vet[marcador] = vet[menor];
            vet[menor] = aux;
        }

        //Aumenta a posição do marcador
        marcador++;
    }
};

//usa o método insertionSort para ordenar o vetor
void insertionSort(int* vet, int tam, int *comparacao, int *troca){
    int aux, pos;

    for(int i=2; i<=tam; i++){
        pos = i - 1;
        aux = vet[i];

        (*comparacao)++;

        while(pos >= 0 && aux < vet[pos]){
            vet[pos+1] = vet[pos];
            pos = pos - 1;
            (*comparacao)++;
            (*troca)++;
        }

        vet[pos+1] = aux;
        (*troca)++;

    }
}

//usa o método mergeSort para ordenar o vetor
void mergeSort(int *vet, int inicio, int fim, int *comparacao, int *troca){
    int meio = (inicio+fim)/2;

    if(inicio < fim){
        mergeSort(vet, inicio, meio, comparacao, troca);
        mergeSort(vet, meio+1, fim, comparacao,troca);
        merge(vet, inicio, meio, fim, comparacao, troca);
    }
}
void merge(int *vet, int inicio, int meio, int fim, int *comparacao, int *troca){
    int v1 = meio - inicio + 1;
    int v2 = fim - meio;

    int *vetor1 = (int*)malloc(v1 * sizeof(int));
    int *vetor2 = (int*)malloc(v2 * sizeof(int));

    for(int i=0; i<v1; i++){
        vetor1[i] = vet[inicio + i];
    }

    for(int i=0; i<v2; i++){
        vetor2[i] = vet[meio + 1 + i];
    }

    int i=0, j=0, k=inicio;

    while(i < v1 && j < v2){
        (*comparacao)++;

        if(vetor1[i] <= vetor2[j]){
            vet[k] = vetor1[i];
            i++;
        }
        else{
            vet[k] = vetor2[j];
            j++;
        }
        k++;
    }

    while(i < v1){
        vet[k] = vetor1[i];
        i++;
        k++;
        (*troca)++;
    }

    while(j < v2){
        vet[k] = vetor2[j];
        j++;
        k++;
        (*troca)++;
    }


    free(vetor1);
    free(vetor2);
}

/* Ordena o vetor usando o algoritmo Quick Sort e conta comparações e trocas */
void quickSort(int *vet, int inicio, int fim, int *comparacao, int *troca){

    if(inicio < fim){
        int pivo = particiona(vet, inicio, fim, comparacao, troca); //Define a posição do pivô
        quickSort(vet, inicio, pivo-1, comparacao, troca); //Chama o quickSort para os elementos antes do pivô
        quickSort(vet, pivo+1, fim, comparacao, troca); //Chama o quickSort para os elementos após o pivô
    }
};

int particiona(int *vet, int inicio, int fim, int *comparacao, int *troca){
    int pivo = vet[inicio]; // Define o pivô como o elemento inicial do vetor
    int pos = inicio; // Inicializa a variável pos com o valor da posição inicial do vetor
    int aux;

    for (int i = inicio + 1; i <= fim; i++) {
        (*comparacao)++; // Conta a comparação entre vet[i] e pivo
        if (vet[i] < pivo) {
            pos++;
            if (i != pos) {
                // Coloca os elementos menores que o pivô à esquerda dos elementos maiores que ele
                aux = vet[i];
                vet[i] = vet[pos];
                vet[pos] = aux;
                (*troca)++; // Conta a troca entre vet[i] e vet[pos]
            }
        }
    }

    // Coloca o pivô na posição correta
    aux = vet[inicio];
    vet[inicio] = vet[pos];
    vet[pos] = aux;
    (*troca)++; // Conta a troca final do pivô com vet[pos]

    // Retorna a posição do pivô
    return pos;
}



//gera o heap maximo
void heapMaximo(int *h, int tam, int *comparacao, int *troca){
    for(int i = tam/2; i >= 1; i--){
        heapify(h, i, tam, comparacao, troca);
    }
}

/* Ordena o vetor representado pela struct heap usando Heap Sort */
//usa o método de heapSort para ordenar o vetor

void heapify(int *h, int tail, int tam, int *comparacao, int *troca){
    int esquerda = 2*tail;
    int direita = 2*tail + 1;
    int maior = tail;

    if(esquerda <= tam){
        (*comparacao)++;
        if(h[esquerda] > h[maior])
            maior = esquerda;
    }

    if(direita <= tam){
        (*comparacao)++;
        if(h[direita] > h[maior])
            maior = direita;
    }

    if(maior != tail){
        int var = h[tail];
        h[tail] = h[maior];
        h[maior] = var;
        (*troca)++;

        heapify(h, maior, tam, comparacao, troca);
   }
}

void heapSort(int *h, int tam, int *comparacao, int *troca){
    heapMaximo(h, tam, comparacao, troca);
    for(int i=tam; i >= 2; i--){
        int var = h[i];
        h[i] = h[1];
        h[1] = var;
        (*troca)++;

        heapify(h, 1, i - 1, comparacao, troca);
    }
}

