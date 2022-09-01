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
void incluir_no_final(lista *l, int x);
int buscar_na_lista(lista * l, int x);
void mostrar_numeros_comuns(lista * l1, lista * l2);
void mostrar_num(lista *li);

void mostrar_lista(lista *l);

int main()
{

    int num, metade ,numero;
    lista * l1, *l2;

    l1 = aloca_lista();
    l2 = aloca_lista();
    printf("\n Digite o valor de N: ");
    scanf("%d",&num);

    metade = num/2;

    for(int i = 0; i < num; i++){
        printf("\n Digite um numero: ");
        scanf("%d",&numero);
        if (i < metade)
            incluir_no_final(l1,numero);
        else
            incluir_no_final(l2,numero);
    }

    printf("\nLista 1:");
    mostrar_lista(l1);
    printf("\nLista 2:");
    mostrar_lista(l2);
    printf("\nNumeros em comun:");
    mostrar_numeros_comuns(l1,l2);

    printf("\n");
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

void incluir_no_final(lista *li, int num){
    
    registro *novo, *aux, *ant = NULL;
    int incluido = 0;

    novo = aloca_registro();

    novo->valor = num;

    if(li->inicio == NULL){
        li->inicio = novo;
    }else{
        aux = li->inicio;
        if(aux->valor > num){
            li->inicio = novo;
            novo->prox = aux;
        }else{
            if(aux->prox == NULL){
                aux->prox = novo;
            }else{
                ant = aux;
                aux = aux->prox;
                while(!incluido){
                    if(aux->valor > num){
                        ant->prox = novo;
                        novo->prox = aux;
                        incluido = 1;
                    }else if(aux->prox == NULL){
                        aux->prox = novo;
                        incluido = 1;
                    }else{
                        ant = aux;
                        aux = aux->prox; 
                    }
                }
            }
        }
    }
    li->qtd++;
}

void mostrar_lista(lista *l){
    
    if (l->inicio == NULL){
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


int buscar_na_lista(lista * l, int x){
    
    if (l->inicio==NULL){
        return 0;
    }

    registro * aux;
    aux = l->inicio;

    while(aux!=NULL){
        if (aux->valor==x){
            return 1;
        }
        aux=aux->prox;
    }
    return 0;
}


void mostrar_numeros_comuns(lista * l1, lista * l2){
    
    registro *aux_1, *aux_2;
    int cont = 0;

    if (l1->inicio==NULL || l2->inicio==NULL){
        printf("\nNao existem numeros em comum");
        return ;
    }else{
        aux_1 = l1->inicio;
        aux_2 = l2->inicio;
        while(aux_1 != NULL && aux_2 != NULL){
            if(aux_1->valor == aux_2->valor){
                printf("\nValor encontrado nas duas listas: %d", aux_1->valor);
                aux_1 = aux_1->prox;
                aux_2 = aux_2->prox;
                cont++;
           }else if(aux_1->valor > aux_2->valor){
               aux_2 = aux_2->prox;
           }else{
               aux_1 = aux_1->prox;
           }
       }
    }
    if(cont == 0){
        printf("\nNao existem numeros em comum!");
    }
}

