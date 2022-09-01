#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    int qtd;
    struct registro *inicio;
} lista;

typedef struct registro
{
    int valor;
    struct registro *prox;
} registro;

lista *aloca_lista();
registro *aloca_registro();
void recebe_num(int *num);
void aloca_num(lista *li, int num);
void mostrar_num(lista *li);

int main()
{
    lista *l1, *l2;
    int num;

    l1 = aloca_lista();
    l2 = aloca_lista();

    for(int i = 0; i < 10; i++){
        recebe_num(&num);
        if(num%2 == 0){
            aloca_num(l1,num);
        }else{
            aloca_num(l2,num);
        }
    }

    printf("\nNumeros Pares:");
    mostrar_num(l1);
    
    printf("Numeros impares:");
    mostrar_num(l2);

    return 0;
}

lista *aloca_lista(){
    
    lista *novo;
    novo = (lista *)malloc(sizeof(lista));
    novo->qtd = 0;
    novo->inicio = NULL;
    return novo;
}

registro *aloca_registro(){
    
    registro *novo;
    novo = (registro *)malloc(sizeof(registro));
    novo->valor = 0;
    novo->prox = NULL;
    return novo;
}

void recebe_num(int *num){

    printf("\nDigite um numero inteiro: ");
    scanf("%d", num);
}

void aloca_num(lista *li, int num){

    registro *novo, *aux;

    novo = aloca_registro();

    novo->valor = num;

    if(li->inicio == NULL){
        li->inicio = novo;
    }else{
        aux = li->inicio;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    li->qtd++;
}

void mostrar_num(lista *li){

    registro *aux;

    if(li->inicio == NULL){
        printf("\nLista vazia!");
    }else{
        aux = li->inicio;
        while(aux != NULL){
            printf("\nValor = %d", aux->valor);
            aux = aux->prox;
        }
    }

    printf("\n");
}