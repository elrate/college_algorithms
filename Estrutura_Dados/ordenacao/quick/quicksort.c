#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int quick(long long int *vetor, long long int inicio, long long int fim);
void trocar(long long int *vetor, long long int *pivor, long long int *aux);
void quick_sort(long long int vet[],long long int inicio,long long int fim);
long long int *aloca_vetor(long long int n);

int main(){

    long long int *vetor;
    long long int n;
    clock_t t;

    srand(time(NULL));
    FILE * arq;

    arq = fopen("temposQuick.csv","a+");

    if(arq==NULL){
        return 0;
    }

    for (n = 100000; n <= 10000000; n = n + 100000)
    {
        vetor = aloca_vetor(n);
        
        t = clock();
        quick_sort(vetor,0,n-1);
        t = clock() - t;
        fprintf(arq,"%lld;%lf\n",n,((double)t)/(CLOCKS_PER_SEC));

        free(vetor);
    }
    fclose(arq);

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