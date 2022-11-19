#include <stdio.h>
#include <stdlib.h>

int valor_global = 1;

//in > out && out < in

typedef struct vertice
{
    int visitado;
    int distancia;
    int in;
    int out;
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
void mostrar_lista(lista *l);
void dfs(vertice *vertices , int x, int distancia,int *ultimo,int pai);

int main(){

    int qtd_vertices;
    vertice *vertices;
    int par_2 = 0;
    int par_1 = 0;
    int ultimo;
    
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

    dfs(vertices,1,0,&ultimo,pai);
    int dnv = ultimo;
    dfs(vertices,dnv,0,&ultimo,pai);
   
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


void mostrar_lista(lista *l){
    registro *aux;

    if (l == NULL){
        printf("\n Lista nula");
        return;
    }

    if (l->inicio == NULL){
        printf("\n Lista vazia");
        return;
    }

    aux = l->inicio;
    while (aux != NULL){
        printf(" -> %d", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

void dfs(vertice *vertices , int x, int distancia,int *ultimo,int pai){
    registro * aux;
    vertices[x].distancia = distancia;
    if(vertices[x].visitado == 1){
        return;
    }else{
        vertices[x].in = valor_global;
        valor_global++;
    }
        
    vertices[x].visitado = 1;

    if (vertices[x].lista_adj==NULL)
        return;
        
    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL){
        if (vertices[aux->valor].visitado==0){
            dfs(vertices,aux->valor,distancia+1); 
        }
        aux = aux->prox;
    }
    vertices[x].out = valor_global;
    valor_global++;

    (*ultimo) = aux->valor;
}