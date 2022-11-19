//Verificacando grafo bipartido

#include <stdio.h>
#include <stdlib.h>

// cor = 1 = Branco
// cor = 0 = Preto
typedef struct vertice
{
    int alterado;
    int cor;
    struct lista *lista_adj;
} vertice;

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

registro *aloca_registro();
lista *aloca_lista();
vertice *aloca_vertice();
void incluir_lista(lista *l, int x);
int verificacao_bipartido(vertice *vertices, lista *l, int x);

int main(){

    int qtd_vertices,verificador = 0;
    vertice *vertices;
    int par_2 = 0;
    int par_1 = 0;
    
    scanf("%d",&qtd_vertices);

    vertices = aloca_vertice();

    for(int i = 0; i < (qtd_vertices-1);i++){

        scanf("%d %d",&par_1,&par_2);

        if (vertices[par_1].lista_adj == NULL){
            vertices[par_1].lista_adj = aloca_lista();
        }

        incluir_lista(vertices[par_1].lista_adj,par_2);

        if (vertices[par_2].lista_adj == NULL){    
            vertices[par_2].lista_adj = aloca_lista();
        }

        incluir_lista(vertices[par_2].lista_adj,par_1);
    }
    for(int i = 1; i <= qtd_vertices && !verificador; i++){
        if(vertices[i].alterado == 0){
            vertices[i].alterado = 1;
            vertices[i].cor = 0;
        }
        verificador = verificacao_bipartido(vertices,vertices[i].lista_adj,vertices[i].cor);
    }
    
    if(verificador == 0) 
        printf("Grafo Bipartido!\n");
    else
        printf("O grafo nao e bipartido!\n");

    return 0;
}

lista *aloca_lista(){
    lista *novo_lista;
    novo_lista = (lista *)calloc(1, sizeof(lista));
    return novo_lista;
}

registro *aloca_registro(){
    registro *novo_registro;
    novo_registro = (registro *)calloc(1, sizeof(registro));
    return novo_registro;
}

vertice *aloca_vertice(){
    vertice *novo_vertice;
    novo_vertice = (vertice *)calloc(1000, sizeof(vertice));
    return novo_vertice;
}

void incluir_lista(lista *l, int x){
    
    if (l == NULL)
        return;

    registro *novo, *aux = NULL, *ant = NULL;
    novo = aloca_registro();
    novo->valor = x;

    if (l->inicio == NULL){
        l->inicio = novo;
    }else{
        int inserido = 0;
        aux = l->inicio;
        while (aux != NULL && !inserido){

            if (aux->valor == novo->valor){
                return;
            }

            if (aux->valor < novo->valor){
                ant = aux;
                aux = aux->prox;
            }else{
                if (ant == NULL)
                    l->inicio = novo;
                else
                    ant->prox = novo;

                novo->prox = aux;
                inserido = 1;
            }
        }
        if (!inserido){
            ant->prox = novo;
            inserido = 1;
        }
    }
    l->qtd++;
    return;
}
int verificacao_bipartido(vertice *vertices, lista *l, int x){
    
    registro *aux;

    if (l == NULL){
        return 0;
    }

    if (l->inicio == NULL){
        return 0;
    }
    aux = l->inicio;
    while (aux != NULL){
        if(vertices[aux->valor].alterado == 0){
            vertices[aux->valor].cor = !x;
            vertices[aux->valor].alterado = 1;
        }else if(vertices[aux->valor].cor == x){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}