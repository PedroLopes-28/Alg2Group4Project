#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "benchmark.h"

/* Estrutura para representar um heap (usado no heapSort) */
struct heap {
    int *vet;  // Vetor que representa o heap
    int tam;   // Tamanho atual do heap
};


/* Gera um vetor com números aleatórios entre 0 e RANGE */
int *geraAleatorios(int tam, int semente){
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

/* Gera um vetor ordenado em ordem crescente (ordem = 0) ou decrescente (ordem = 1) */
int *geraOrdenados(int tam, int ordem){
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

/* Gera um vetor quase ordenado, com base na porcentagem de desordem desejada */
int *geraQuaseOrdenados(int tam, int porcentagem){
    //Define o número de trocas a serem feitas baseada na porcentagem indicada
    int numTrocas = (int)(tam * porcentagem / 100);

    //Inicializa a semente geradora de números com um valor padrão
    srand(2);

    //Gera vetor ordenado
    int *vet = geraOrdenados(tam, 0);

    //Faz trocas aleatórias
    for(int i = 0; i<numTrocas; i++){
        int a = rand() % tam;
        int b = rand() % tam;
        if(a != b){ //Não realiza a troca se for o mesmo elemento
            int aux = vet[a];
            vet[a] = vet[b];
            vet[b] = aux;
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
            //Aumenta o número de trocas
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
    int aux, pos, posicaoEncontrada;

    for(int i=1; i<tam; i++){
        pos = i - 1;     // Posição anterior à atual
        aux = vet[i];    // Armazena o valor atual na variável aux
        posicaoEncontrada = 0; 
        
        // Move os elementos maiores que aux para a direita
        while(pos >= 0 && !posicaoEncontrada){ 
            //Aumenta o número de comparações
            (*comparacao)++;
          
            // Compara se o valor atual é menor
            if(aux < vet[pos]){   
                //Aumenta o número de trocas
                (*troca)++;
                vet[pos+1] = vet[pos];   // Move o valor maior para frente
                pos = pos - 1;           // Itera o vetor para a esquerda
                
            }
            else{
                posicaoEncontrada = 1;    // Se for maior, a posição foi encontrada, então sai do while
            }
        }
        
        // Insere o valor do aux na posição certa
        vet[pos+1] = aux;

    }
}

//usa o método mergeSort para ordenar o vetor
void mergeSort(int *vet, int inicio, int fim, int *comparacao, int *troca){
    int meio = (inicio+fim)/2;  // Divide o vetor ao meio
    
    // Verifica se ainda existe elementos a dividir
    if(inicio < fim){
        mergeSort(vet, inicio, meio, comparacao, troca);  // Chama o mergeSort para a metade da esquerda
        mergeSort(vet, meio+1, fim, comparacao,troca);  // Chama o mergeSort para a metade da direita
        merge(vet, inicio, meio, fim, comparacao, troca);  // Combina as duas metades já ordenadas
    }
}

/* Função auxiliar do Merge Sort para mesclar duas partes do vetor */
void merge(int *vet, int inicio, int meio, int fim, int *comparacao, int *troca){
    // Tamanho dos vetores 1 e 2
    int v1 = meio - inicio + 1;  
    int v2 = fim - meio;
    
    // Aloca espaço para os 2 novos vetores
    int *vet1 = (int*)malloc(v1 * sizeof(int));
    int *vet2 = (int*)malloc(v2 * sizeof(int));
    
    // Copia os elementos do primeiro vetor
    for(int i=0; i<v1; i++){
        vet1[i] = vet[inicio + i];
    }
    
    // Copia os elementos do segundo vetor
    for(int i=0; i<v2; i++){
        vet2[i] = vet[meio + 1 + i];
    }

    int i=0, j=0, k=inicio;
    
    // Compara os elementos do vetor 1 e 2 e insere o menor no vetor original
    while(i < v1 && j < v2){
        (*comparacao)++;

        if(vet1[i] <= vet2[j]){
            vet[k] = vet1[i];
            i++;
        }
        else{
            vet[k] = vet2[j];
            j++;
        }
        k++;
    }
    
    // Copia o que sobrou do primeiro vetor
    while(i < v1){
        vet[k] = vet1[i];
        i++;
        k++;
        (*troca)++;
    }
    
    // Copia o que sobrou do segundo vetor
    while(j < v2){
        vet[k] = vet2[j];
        j++;
        k++;
        (*troca)++;
    }
    
    // Desaloca os dois vetores que foram usados para ordenar o vetor principal
    free(vet1);
    free(vet2);
}

/* Ordena o vetor usando o algoritmo Quick Sort e conta comparações e trocas */
void quickSort(int *vet, int inicio, int fim, int *comparacao, int *troca){

    if(inicio < fim){
        int pivo = particiona(vet, inicio, fim, comparacao, troca); //Define a posição do pivô
        quickSort(vet, inicio, pivo-1, comparacao, troca); //Chama o quickSort para os elementos antes do pivô
        quickSort(vet, pivo+1, fim, comparacao, troca); //Chama o quickSort para os elementos após o pivô
    }
};

/* Função auxiliar do Quick Sort que particiona o vetor */
int particiona(int *vet, int inicio, int fim, int *comparacao, int *troca){
    int pivo = vet[inicio]; // Define o pivô como o elemento inicial do vetor
    int pos = inicio; // Inicializa a variável pos com o valor da posição inicial do vetor
    int aux;

    for (int i = inicio + 1; i <= fim; i++) {
        // Conta a comparação entre vet[i] e pivo
        (*comparacao)++; 

        if (vet[i] < pivo) {
            pos++;
            if (i != pos) {
                // Conta a troca entre vet[i] e vet[pos]
                (*troca)++; 

                // Coloca os elementos menores que o pivô à esquerda dos elementos maiores que ele à direita
                aux = vet[i];
                vet[i] = vet[pos];
                vet[pos] = aux;
                
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

// Coloca um certo valor em sua posição, seguindo as propriedades de heap
void heapify(int *h, int tail, int tam, int *comparacao, int *troca){
    // Determina os valores das posições dos filhos do tail
    int esquerda = 2*tail;
    int direita = 2*tail + 1;
    int maior = tail;
    
    // Verifica se o filho da esquerda é maior que o pai (se houver)
    if(esquerda <= tam){
        (*comparacao)++;
        if(h[esquerda] > h[maior])
            maior = esquerda;
    }

    // Verifica se o filho da direita é maior que o pai (se houver)
    if(direita <= tam){
        (*comparacao)++;
        if(h[direita] > h[maior])
            maior = direita;
    }
    
    // Se um dos filhos for maior que o pai, realiza a troca e reaplica o heapify no restante da árvore
    if(maior != tail){
        int var = h[tail];
        h[tail] = h[maior];
        h[maior] = var;
        (*troca)++;

        heapify(h, maior, tam, comparacao, troca);
   }
}

// Constrói uma heap máxima a partir do vetor
void heapMaximo(int *h, int tam, int *comparacao, int *troca){
    // Chama a função heapify para os nós internos, até o vetor seguir as propriedades da heap
    for(int i = tam/2; i >= 1; i--){
        heapify(h, i, tam, comparacao, troca);
    }
}

// Implementa o algoritmo heapSort para ordenar o vetor
void heapSort(int *h, int tam, int *comparacao, int *troca){
    // Constrói uma heap máxima a partir do vetor, garantindo a propriedade de heap
    heapMaximo(h, tam, comparacao, troca);
    
    // Realiza a ordenação
    for(int i=tam; i >= 2; i--){
        // Move o maior elemento(raiz) para o final do vetor
         int var = h[i];
         h[i] = h[1];
         h[1] = var;
         (*troca)++;
        // Reaplica a propriedade de heap ao restante do vetor(excluindo a parte já ordenada)
        heapify(h, 1, i - 1, comparacao, troca);
    }
}
