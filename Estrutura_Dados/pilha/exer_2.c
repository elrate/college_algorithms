#include <stdio.h>
#include <stdlib.h>

typedef struct pilha{
    struct registro *topo;
}pilha;

typedef struct registro{
    int valor;
    struct registro *ant;
}registro;

pilha *aloca_pilha();
registro *aloca_registro();
void menu(pilha *p);
void push(pilha *p, int num);
int pop(pilha *p);
int stackpop(pilha *p);
int empty(pilha *p);
pilha *inverte_pilha(pilha *p);

int main(){

    pilha *p;
    p = aloca_pilha();

    menu(p);

    printf("\n");

    return 0;
}

pilha *aloca_pilha(){
    
    pilha *novo;
    novo = (pilha*)malloc(sizeof(pilha));
    novo->topo = NULL;
    return novo;
}

registro *aloca_registro(){

    registro *novo;
    novo = (registro*)malloc(sizeof(registro));
    novo->valor = 0;
    novo->ant = NULL;
    return novo;
}

void menu(pilha *p){
    
    int opcao, num;
    do
    {
        printf("\n 1 - Push");
        printf("\n 2 - Pop");
        printf("\n 3 - Stackpop");
        printf("\n 4 - Empty");
        printf("\n 5 - Inverte pilha");
        printf("\n 6 - Sair");
        printf("\nOpcao: ");
        scanf("%d",&opcao);

        switch (opcao)
        {
        case 1:
            printf("\nDigite um numero: ");
            scanf("%d", &num);
            push(p, num);
            break;
        case 2:
            if(!empty(p)){
                num = pop(p);
                printf("\nNumero que saiu : %d",num);    
            }else{
                printf("\nPilha vazia!");
            }
            printf("\n");
            break;
        case 3:
            if(!empty(p)){
                num = stackpop(p);
                printf("\nNumero que esta para sair : %d",num);
            }else{
                printf("\nPilha vazia!");
            }
            printf("\n");
            break;
        case 4:
            if(empty(p))
                printf("\nPilha vazia!");
            else
                printf("\nA pilha nao esta vazia!");
            break;
        case 5:
            if(!empty(p)){
                p = inverte_pilha(p);
            }else{
                printf("\nPilha vazia!\n");
            }
            break;
        case 6:
            printf("\nSaindo do programa");
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    } while (opcao != 6);
}

void push(pilha *p, int num){

    registro *novo;
    novo = aloca_registro();
    novo->valor = num;
    
    if(empty(p)){
        p->topo = novo;
    }else{
        novo->ant = p->topo;
        p->topo = novo;
    }
}

int pop(pilha *p){

    if(empty(p)){
        printf("\nPilha vazia!");
        return -1;
    }else{
        registro *aux;
        int num;
        aux = p->topo;
        num = aux->valor;
        p->topo = aux->ant;
        free(aux);
        return num;
    }
}

int stackpop(pilha *p){

    if(empty(p)){
        printf("\nPilha vazia!");
        return -1;
    }else{
        return p->topo->valor;
    }
}

int empty(pilha *p){

    if(p->topo == NULL){
        return 1;
    }else{
        return 0;
    }
}

pilha *inverte_pilha(pilha *p){

    if(empty(p)){
        printf("\nPilha vazia!");
        return p;
    }else{
        pilha *p_invertida;
    
        p_invertida = aloca_pilha();

        while((!empty(p))){
            push(p_invertida, pop(p));
        }
        return p_invertida;
    }
}