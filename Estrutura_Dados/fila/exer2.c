#include <stdio.h>
#include <stdlib.h>

typedef struct fila{
    int tamanho;
    struct elemento *inicio;
    struct elemento *fim;
}fila;

typedef struct elemento{
    int valor;
    struct elemento *prox;
}elemento;

fila* aloca_fila();
elemento* aloca_elemento();
void insert(fila *f,int valor);
int empty(fila *f);
int remove_ultimo(fila *f);

int main(){
    
    int n;
    fila *f;
    
    printf("\nDigite o numero de cartas que deseja alocar: ");
    scanf("%d",&n);

    while(n > 0){
        f = aloca_fila();

        for(int i = 1; i <= n; i++){
            insert(f, i);
        }

        printf("\nDiscarded cards:");
        while(f->tamanho > 1){
            printf(" %d",remove_ultimo(f));
            if(f->tamanho > 1){
                printf(",");
            }
        }

        printf("\nRemaining card: %d", f->inicio->valor);

        free(f->inicio);
        free(f->fim);

        printf("\nDigite o numero de cartas que deseja alocar: ");
        scanf("%d",&n);
    }

return 0;
}

fila* aloca_fila(){
    fila *novo;
    novo = (fila*) malloc(sizeof(fila));
    novo->tamanho = 0;
    novo->inicio = NULL;
    novo->fim = NULL;
    return novo;
}
elemento* aloca_elemento(){
    elemento *novo;
    novo = (elemento*)malloc(sizeof(elemento));
    novo->valor = 0;
    novo->prox = NULL;
    return novo;
}
void insert(fila *f,int valor){

    elemento *novo;
    novo = aloca_elemento();
    novo->valor = valor;

    if(empty(f)){
        f->inicio = novo;
    }else{
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tamanho++;
}

int empty(fila *f){

    if(f->inicio == NULL && f->fim == NULL){
        return 1;
    }else{
        return 0;
    } 
}

int remove_ultimo(fila *f){

    if(empty(f)){
        return -1;
    }
    
    elemento *aux;
    int numero;
    aux = f->inicio;

    if(f->tamanho == 2){
        f->inicio = aux->prox;
        f->fim  = aux->prox;
    }else{
        f->inicio = aux->prox->prox;

        f->fim->prox = aux->prox;
        f->fim = aux->prox;
        aux->prox->prox = NULL;
    }

    numero = aux->valor;
    f->tamanho--;

    free(aux);
    return numero;
}
