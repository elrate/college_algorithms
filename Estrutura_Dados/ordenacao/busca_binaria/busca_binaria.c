#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int busca_sequencial(long long int vetor[], long long int tamanho,long long int numero_escolhido);
int busca_binaria(long long int vetor[],long long int numero_escolhido,long long int inicio, long long int fim);

int main(){

    long long int *vetor;
    long long int tamanho,numero;
    int verificador;
    clock_t t;

    printf("\nDigite o Tamanho do vetor: ");
    scanf("%lld",&tamanho);

    vetor = (long long int*)calloc(tamanho,sizeof(long long int));

    for(int i=0; i<tamanho; i++){
        printf("Digite um numero: ");
        scanf("%lld",&vetor[i]);
    }

    printf("Digite o numero que deseja encontrar: ");
    scanf("%lld",&numero);

    t = clock();
    verificador = busca_sequencial(vetor,tamanho,numero);
    t = clock() - t;

    printf("\nTempo Sequencial: %lf", ((double)t)/(CLOCKS_PER_SEC));

    t = clock();
    verificador = busca_binaria(vetor,numero,0,tamanho-1);
    t = clock() - t;

    printf("\nTempo Binario: %lf", ((double)t)/(CLOCKS_PER_SEC));

    if(verificador == 0){
        printf("\nNumero (%lld) nao foi encontrado no vetor!\n", numero);
    }else{
        printf("\nNumero (%lld) foi encontrado no vetor!\n", numero);
    }

    return 0;
}

int busca_sequencial(long long int vetor[], long long int tamanho,long long int numero_escolhido){

    for(int i = 0; i < tamanho; i++){
        if(vetor[i] == numero_escolhido){
            return 1;
        }
    }

    return 0;
}

int busca_binaria(long long int vetor[],long long int numero_escolhido,long long int inicio, long long int fim){

    long long int metade;

    while(inicio <= fim){
        
        metade = (inicio + fim)/2;

        if(vetor[metade] == numero_escolhido){
            return 1;
        }else{
            if(vetor[metade] < numero_escolhido){
                inicio = metade + 1;
            }else{
                fim = metade - 1;
            }
        }
    }

    return 0;
}