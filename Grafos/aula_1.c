//Criando uma lista e matrix de adjacencia

#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    int qtd;
    struct registro *inicio;
    struct registro *fim;
} lista;

typedef struct registro
{
    int valor;
    struct registro *prox_vertice;
    struct registro *ant_vertice;
    struct registro *prox_ligacao;
} registro;

void mostrar_matriz(int matriz[999][999],int qtd_num,lista *l);
int criar_matriz(int matriz[999][999],int qtd_num,int maior);
lista *aloca_lista();
registro *aloca_registro();
void incluir_vertice(lista *l, int x);
void incluir_ligacao(lista *li, int num);
void mostrar_lista(lista *l);

int main(){

    int qtd_num = 0;
    int maior = 0;
    int matriz[999][999];
    lista *lista_adjacente;

    lista_adjacente = aloca_lista();

    printf("Quantos pares deseja colocar? ");

    scanf("%d",&qtd_num);

    maior = criar_matriz(matriz,qtd_num,maior);    

    mostrar_matriz(matriz,maior,lista_adjacente);

    mostrar_lista(lista_adjacente);
    
    return 0;
}

int criar_matriz(int matriz[999][999],int qtd_num,int maior){
    int num_1 = 0;
    int num_2 = 0;

    for(int i = 0;i < qtd_num;i++){
        printf("\nInsira o par %d: ", i+1);
        scanf("%d %d", &num_1,&num_2);
        matriz[num_1][num_2] = 1;
        matriz[num_2][num_1] = 1;
        matriz[num_1][num_1] = 1;
        matriz[num_2][num_2] = 1;
        if(maior < num_1){
            maior = num_1;
        }
        if(maior < num_2){
            maior = num_2;
        }
    }
    return maior;
}

void mostrar_matriz(int matriz[999][999],int maior,lista *l){
    printf("\nMatriz de adjacencia que representa esse grafo:");
    for(int i = 0; i <= maior; i++){
        if(matriz[i][i] == 1){
            incluir_vertice(l,i);
            if(i < 10){
                printf("\nVertice: %d   | ",i);
            }else if(i < 100){
                printf("\nVertice: %d  | ",i);
            }else{
                printf("\nVertice: %d | ",i);
            }
            for(int j = 0; j <= maior; j++){
                if(matriz[j][j] == 1){
                    if(matriz[i][j] == 1 && i != j){
                        incluir_ligacao(l,j);
                    }
                    printf("%d ",matriz[i][j]);
                }
            }
            printf("|");
        }
    }
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
    novo = (registro *)malloc(sizeof(registro));
    novo->valor = 0;
    novo->prox_vertice = NULL;
    novo->ant_vertice = NULL;
    novo->prox_ligacao = NULL;
    return novo;
}

void incluir_vertice(lista *l, int num){
    
    registro *novo, *aux;

    novo = aloca_registro();
    novo->valor = num;

    if(l->inicio == NULL && l->fim == NULL){
        l->inicio = novo;
        l->fim = novo;
    }else{
        aux = l->fim;
        l->fim = novo;
        aux->prox_vertice = novo;
        novo->ant_vertice = aux;
    }
}
void incluir_ligacao(lista *l, int num){
    
    registro *novo, *aux;
    novo = aloca_registro();
    novo->valor = num;

    if(l->fim->prox_ligacao == NULL){
        l->fim->prox_ligacao = novo;
    }else{
        aux = l->fim->prox_ligacao;
        while (aux->prox_ligacao != NULL){
            aux = aux->prox_ligacao;
        }
        aux->prox_ligacao = novo;
    }
}

void mostrar_lista(lista *l){
    printf("\n\nLista de adjacencia que representa esse grafo:");

    int valor = 0;
    if (l->inicio == NULL){
        printf("\n Lista vazia");
    }else{
        registro *aux,*aux_2;
        aux = l->inicio;

        while (aux != NULL){
            valor = aux->valor;
            if(valor < 10){
                printf("\nVertice: %d   | ",valor);
            }else if(valor < 100){
                printf("\nVertice: %d  | ",valor);
            }else{
                printf("\nVertice: %d | ",valor);
            }
            aux_2 = aux;
            while(aux_2->prox_ligacao != NULL){
                printf("%d ",aux_2->prox_ligacao->valor);
                aux_2 = aux_2->prox_ligacao;
            }
            printf("|");
            aux = aux->prox_vertice;
        }
    }
}