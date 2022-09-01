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

void recebe_opcao(int *opcao);
lista *aloca_lista();
registro *aloca_registro();
void inclui_na_lista(lista *li);
void mostrar_lista(lista *li);
void mostrar_pares(lista *li);

int main(){

    int opcao;
    lista *li;

    li = aloca_lista();

    recebe_opcao(&opcao);

    while(opcao != 0){
        
        if(opcao == 1){
            inclui_na_lista(li);
        }
        if(opcao == 2){
            mostrar_lista(li);
            printf("\n");
        }
        if(opcao == 3){
            mostrar_pares(li);
            printf("\n");
        }
        recebe_opcao(&opcao);   
    }
    printf("\n");
    return 0;
}

void recebe_opcao(int *opcao){
        
    printf("\nCaso queira inserir um numero na lista, digite - 1");
    printf("\nCaso queira mostrar a lista completa, digite - 2");
    printf("\nCaso queira mostrar os numeros pares da lista, digite - 3");
    printf("\nSair - 0");
    printf("\nOpcao: ");
    scanf("%d",opcao);

    while((*opcao > 3) || (*opcao < 0)){
        printf("\nOpcao invalida!");
        printf("\nOpcao: ");
        scanf("%d",opcao);
    } 
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

void inclui_na_lista(lista *li){

    int num_escolhido;
    registro *novo, *aux;

    novo = aloca_registro();
    
    printf("\nDigite um numero inteiro: ");
    scanf("%d",&num_escolhido);

    novo->valor = num_escolhido;

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

void mostrar_lista(lista *li){

    registro *aux;
    int cont = 1;

    if(li->inicio == NULL){
        printf("\nLista vazia!\n");
    }else{
        aux =li->inicio;
        while(aux != NULL){
            printf("\nValor %d = %d", cont, aux->valor);
            aux = aux->prox;
            cont++;
        }
    }
}

void mostrar_pares(lista *li){

    registro *aux;
    int cont = 0;

    if(li->inicio == NULL){
        printf("\nLista vazia!\n");
    }else{
        aux =li->inicio;
        while(aux != NULL){
            if(aux->valor%2==0){
                printf("\nValor = %d", aux->valor);
                cont++;
            }
            aux = aux->prox;
        }
        if(cont==0){
        printf("\nA Lista nao possui numeros pares!");
        }
    }
}