#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int qtd;
    struct registro *inicio;
}lista;
typedef struct registro{
    int valor;
    struct registro *prox;
}registro;

lista *aloca_lista();
registro *aloca_registro();
int par_ou_impar(int qtd_escolhida);
void incluir_num(lista *li, int num);
void encontrar_num_iguais(lista *l1, lista *l2);
int verificacao_de_valor(lista *li, int num);
void mostrar_num(lista *li);

int main(){

    lista *l1, *l2;
    int qtd_escolhida, aux, num_escolhido;

    l1 = aloca_lista();
    l2 = aloca_lista();

    printf("\nDigite a quantidade de numeros que voce deseja alocar: ");
    scanf("%d", &qtd_escolhida);

    aux = par_ou_impar(qtd_escolhida);

    for(int i=1; i<=qtd_escolhida; i++){
        
        printf("\nDigite um numero: ");
        scanf("%d", &num_escolhido);

        if(aux == 1){
            if(i <= (qtd_escolhida/2)){
                incluir_num(l1,num_escolhido);
            }else{
                incluir_num(l2,num_escolhido);
            }
        }else{
            if(i <= ((qtd_escolhida/2) + 1)){
                incluir_num(l1,num_escolhido);
            }else{
                incluir_num(l2,num_escolhido);
            }
        }
    }

    encontrar_num_iguais(l1,l2);

    printf("\n");
    return 0;
}

lista *aloca_lista(){

    lista *novo;
    novo = (lista*)malloc(sizeof(lista));
    novo->qtd = 0;
    novo->inicio = NULL;

    return novo;
}

registro *aloca_registro(){

    registro *novo;
    novo = (registro*)malloc(sizeof(registro));
    novo->valor = 0;
    novo->prox = NULL;

    return novo;
}

int par_ou_impar(int qtd_escolhida){

    if(qtd_escolhida%2 == 0){
        return 1;
    }else{
        return 0;
    }
}

void incluir_num(lista *li, int num){

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

void encontrar_num_iguais(lista *l1, lista *l2){

    lista *l3;
    int verificador, cont = 0;

    l3 = aloca_lista();

    if(l1->qtd == 0){
        printf("\nAs listas estao vazias!\n");
    }else if(l2->qtd == 0){
        printf("\nAs listas nao possuem valores iguais\n");
    }else{
        registro *aux_1, *aux_2;
        aux_1 = l1->inicio;
        aux_2 = l2->inicio;

        while(aux_1 != NULL){
            while(aux_2 != NULL){
                if(aux_1->valor == aux_2->valor){
                    verificador = verificacao_de_valor(l3, aux_1->valor);
                    if(verificador == 0){
                        incluir_num(l3, aux_1->valor);
                        cont++;
                    }
                }
                aux_2 = aux_2->prox;
            }
            aux_2 = l2->inicio;
            aux_1 = aux_1->prox;
        }
    }
    if(cont == 0){
        printf("\nAs listas nao possuem valores iguais\n");
    }else{
        printf("\nNumeros que ambas as listas possuem:");
        mostrar_num(l3);
    }
}

int verificacao_de_valor(lista *li, int num){

    registro *aux;
    int verificador = 0;

    if(li->inicio != NULL){
        aux = li->inicio;

        while(aux != NULL){
            if(aux->valor == num){
                verificador = 1;
            }
            aux = aux->prox;
        }
    }
    
    return verificador;
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