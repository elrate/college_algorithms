#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int quick(long long int *vetor, long long int inicio, long long int fim);
void trocar(long long int *vetor, long long int *pivor, long long int *aux);
void quick_sort(long long int vet[],long long int inicio,long long int fim);

int main(){

    long long int vetor[10];

    for(int i = 0; i < 10; i++){
        scanf("%lld",&vetor[i]);
    }

    quick_sort(vetor,0,9);

    for(int i = 0; i < 10; i++){
        printf("|%lld |",vetor[i]);
    }
    return 0;
}

void quick_sort(long long int vet[],long long int inicio,long long int fim){
	
    if(inicio < fim){
		long long int pivor; 

        pivor = quick(vet, inicio, fim);
		
		quick_sort(vet, inicio, pivor - 1);
		quick_sort(vet, pivor + 1, fim);
	}
}

long long int quick(long long int *vetor, long long int inicio, long long int fim){

    long long int pivor, aux;

    pivor = inicio;
    aux = fim;

    while(pivor != aux){
        if(pivor < aux){
            if(vetor[pivor] > vetor[aux]){
                trocar(vetor,&pivor,&aux);
            }else{
                aux--;
            }
        }else{
            if(vetor[pivor] < vetor[aux]){
                trocar(vetor,&pivor,&aux);
            }else{
                aux++;
            }
        }
    }

    return pivor;
}

void trocar(long long int *vetor, long long int *pivor, long long int *aux){

    long long int numero;

    numero = vetor[*pivor];
    vetor[*pivor] = vetor[*aux];
    vetor[*aux] = numero;

    numero = *pivor;
    *pivor = *aux;
    *aux = numero;
}

