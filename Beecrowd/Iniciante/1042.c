#include <stdio.h>

void insertion_sort(int vetor[]);

int main(){

    int vet[3];
    int valor_1, valor_2,valor_3;

    scanf("%d %d %d",&vet[0],&vet[1],&vet[2]);

    valor_1 = vet[0];
    valor_2 = vet[1];
    valor_3 = vet[2];

    insertion_sort(vet);

    for(int i=0;i<3;i++){
        printf("%d\n",vet[i]);
    }
    printf("\n");
    printf("%d\n",valor_1);
    printf("%d\n",valor_2);
    printf("%d\n",valor_3);
    return 0;
}

void insertion_sort(int vetor[]){

    int i, j, aux;

    for(i = 1; i < 3; i++){
        aux = vetor[i];
        for(j = i - 1; j >= 0 && aux < vetor[j]; j--){
            vetor[j + 1] = vetor[j];
        }
        vetor[j + 1] = aux;
    }
}