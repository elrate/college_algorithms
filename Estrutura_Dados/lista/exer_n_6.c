#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int qtd;
    struct registro *inicio;
    struct registro *fim;
}lista;

typedef struct registro{
    int valor;
    struct registro *prox;
    struct registro *ant;
}registro;

lista *aloca_lista();
registro *aloca_registro();
void menu(lista *l);
void registra_no_inicio(lista *l, int num);
void registra_no_final(lista *l, int num);
void mostrar_lista(lista *l);
void remover_da_lista(lista *l, int num);

int main(){
    
    lista *l;

    l = aloca_lista();
    
    menu(l);

    return 0;
}

void menu(lista *l){
    int opcao, num;

    do{
        printf("\n 1 - Incluir no inicio da lista");
        printf("\n 2 - Incluir no fim da lista");
        printf("\n 3 - Mostrar lista");
        printf("\n 4 - Mostrar primos da lista");
        printf("\n 5 - Mostrar lista de tras pra frente");
        printf("\n 6 - Remover elemento da lista");
        printf("\n 7 - Remover primos da lista");
        printf("\n 8 - Sair");
        scanf("%d", &opcao);

        switch(opcao) 
        {
        case 1:
            printf("\nDigite o numero que deseja inserir no inicio da lista");
            scanf("%d", &num);
            registra_no_inicio(l, num);
            break;
        case 2:
            printf("\nDigite o numero que deseja inserir no final da lista");
            scanf("%d", &num);
            registra_no_final(l, num);
            break;
        case 3:
            printf("\nLista:");
            mostrar_lista(l);
            break;
        case 4:
            printf("\nVazio");
            break;
        case 5:
            printf("\nVazio");
            break;
        case 6:
            printf("\nDigite o numero que deseja remover: ");
            scanf("%d", &num);
            remover_da_lista(l, num);
            break;
        case 7:
            printf("\nVazio");
            break;
        case 8:
            printf("\nSaindo do programa");
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    }while(opcao != 8);
}

lista *aloca_lista(){

    lista *novo;
    novo = (lista *)malloc(sizeof(lista));
    novo->qtd = 0;
    novo->inicio = NULL;
    novo->fim = NULL;
    return novo;
}

registro *aloca_registro(){
    
    registro *novo;
    novo = (registro*)malloc(sizeof(registro));
    novo->valor = 0;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

void registra_no_inicio(lista *l, int num){

    registro *novo, *aux;

    novo = aloca_registro();
    novo->valor = num;

    if(l->inicio == NULL && l->fim == NULL){
        l->inicio = novo;
        l->fim = novo;
    }else{
        aux = l->inicio;
        l->inicio = novo;
        novo->prox = aux;
        aux->ant = novo;
    }
    l->qtd++;
}

void registra_no_final(lista *l, int num){

    registro *novo, *aux;

    novo = aloca_registro();
    novo->valor = num;

    if(l->inicio == NULL && l->fim == NULL){
        l->inicio = novo;
        l->fim = novo;
    }else{
        aux = l->fim;
        l->fim = novo;
        aux->prox = novo;
        novo->ant = aux;
    }
    l->qtd++;
}

void mostrar_lista(lista *l){
    
    if (l->inicio == NULL && l->fim == NULL) {
        printf("\n Lista vazia");
    }else{
        registro *aux;
        aux = l->inicio;
        while (aux != NULL){
            printf("\nValor = %d", aux->valor);
            aux = aux->prox;
        }
    }
}

void remover_da_lista(lista *l, int num){
    
    if (l->inicio == NULL && l->fim == NULL)
    {
        printf("\n Lista vazia");
        return;
    }

    registro *aux = NULL;
    aux = l->inicio;

    while (aux != NULL)
    {
        if (aux->valor == num)
        {
            if (aux->ant == NULL)
            {
                l->inicio = aux->prox;
                aux->prox->ant = NULL;
            }
            else
            {
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
            }
            free(aux);
            l->qtd--;
            printf("\n Numero removido");
            return;
        }
        else
        {
            aux = aux->prox;
        }
    }

    printf("\n Numero nao esta na lista");
    return;
}