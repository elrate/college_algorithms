#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

long long int *aloca_vetor(long long int n);
void insertion_sort(long long int vetor[], long long int n);

int main(){

    long long int *vetor;
    long long int n;
    srand(time(NULL));
    double tempo_1,tempo_2;
    FILE * arq;

    arq = fopen("tempos.csv","a+");

    if(arq==NULL){
        return 0;
    }
    
    printf("\nDigite o tamanho do vetor: ");
    scanf("%lld", &n);

    vetor = aloca_vetor(n);

    printf("\nSem ordenar: \n");
    for(int i=0; i<n; i++){
        printf("%lld ",vetor[i]);
    }

    insertion_sort(vetor,n);

    printf("\nOrdenardo: \n");
    for(int i=0; i<n; i++){
        printf("%lld ",vetor[i]);
    }

    return 0;
}

long long int *aloca_vetor(long long int n){

    long long int *vetor, i, sorteio, aux;

    vetor = (long long int *)calloc(n, sizeof(long long int));

    for (i = 0; i < n; i++)
    {
        vetor[i] = i + 1;
    }

    for (i = 0; i < n; i++)
    {
        sorteio = rand() % n;
        aux = vetor[i];
        vetor[i] = vetor[sorteio];
        vetor[sorteio] = aux;
    }

    return vetor;
}

void insertion_sort(long long int vetor[], long long int n){

    int i, j, aux;

    for(i = 1; i < n; i++){
        aux = vetor[i];
        for(j = i - 1; j >= 0 && aux < vetor[j]; j--){
            vetor[j + 1] = vetor[j];
        }
        vetor[j + 1] = aux;
    }
}