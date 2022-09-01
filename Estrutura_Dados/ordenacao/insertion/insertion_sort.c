#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int *aloca_vetor(long long int n);
void insertion_sort(long long int vetor[], long long int n);

int main(){

    long long int *vetor;
    long long int n;
    clock_t t;
    srand(time(NULL));
    FILE * arq;

    arq = fopen("tempos.csv","a+");

    if(arq==NULL){
        return 0;
    }
    
    printf("\nDigite o tamanho do vetor: ");
    scanf("%lld", &n);

    for (n; n <= 10000; n = n + 1000)
    {
        vetor = aloca_vetor(n);
        t = clock();
        insertion_sort(vetor,n);
        t = clock() - t;
        fprintf(arq,"%lld;%lf\n",n,((double)t)/((CLOCKS_PER_SEC/1000)));

        free(vetor);
    }
    fclose(arq);

    printf("\n");
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