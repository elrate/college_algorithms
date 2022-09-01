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
int remover(fila *f);
int empty(fila *f);
int size(fila *f);
int front(fila *f);
void menu(fila *f);

int main(){

    fila *f;
    f = aloca_fila();
    menu(f);

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

int remover(fila *f){

    if(empty(f)){
        return -1;
    }else{
        elemento *aux;
        int num_removido;

        aux = f->inicio;
        f->inicio = aux->prox;
        num_removido = aux->valor;

        if(aux->prox == NULL){
            f->fim = NULL; 
        }

        f->tamanho--;
        free(aux);
        return num_removido;
    }
}

int empty(fila *f){

    if(f->inicio == NULL && f->fim == NULL){
        return 1;
    }else{
        return 0;
    } 
}

int size(fila *f){

    return f->tamanho;
}

int front(fila *f){

     if(empty(f)){
        return -1;
    }else{
        return f->inicio->valor;
    }
}

void menu(fila *f){

    int opcao, num;
    do
    {
        printf("\n 1 - Insert");
        printf("\n 2 - Remove");
        printf("\n 3 - front");
        printf("\n 4 - Empty");
        printf("\n 5 - Size");
        printf("\n 6 - Sair");
        printf("\nOpcao: ");
        scanf("%d",&opcao);

        switch (opcao)
        {
        case 1:
            printf("\nDigite um numero: ");
            scanf("%d", &num);
            insert(f,num);
            break;
        case 2:
            if(empty(f)){
                printf("\nFila vazia!\n");
            }else{
                printf("\nNumero que saiu : %d\n", remover(f));  
            }
            break;
        case 3:
            if(empty(f)){
                printf("\nFila vazia!\n");
            }else{
                printf("\nNumero que esta para sair : %d\n",front(f));
            }
            break;
        case 4:
            if(empty(f)){
                printf("\nFila vazia!\n");  
            }else{
                printf("\nA fila possui elementos!\n");
            }
            break;
        case 5:
            printf("\nO tamanho da fila e: %d\n", size(f));
            break;
        case 6:
            printf("\nSaindo do programa\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
            break;
        }
    } while (opcao != 6);
}