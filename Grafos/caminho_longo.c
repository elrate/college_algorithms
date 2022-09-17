#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int distancia;
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
void dfs(vertice *vertices , int x, int distancia,int *ultimo, int ver_visit);

int main(){

    int qtd_vertices;
    vertice *vertices;
    int par_2 = 0;
    int par_1 = 0;
    int ultimo = 0;
    int primeiro;
    
    scanf("%d",&qtd_vertices);

    vertices = aloca_vertice();

    for(int i = 0; i < (qtd_vertices-1);i++){

        scanf("%d %d",&par_1,&par_2);
        if(i == qtd_vertices-2)
            primeiro = par_2;

        if (vertices[par_1].lista_adj == NULL){
            vertices[par_1].lista_adj = aloca_lista();
        }

        incluir_lista(vertices[par_1].lista_adj,par_2);

        if (vertices[par_2].lista_adj == NULL){    
            vertices[par_2].lista_adj = aloca_lista();
        }

        incluir_lista(vertices[par_2].lista_adj,par_1);
    }

    dfs(vertices,primeiro,0,&ultimo,1);
    int dnv = ultimo;
    printf("%d\n",dnv);
    ultimo = 0;
    dfs(vertices,dnv,0,&ultimo,2);

    printf("%d\n",vertices[ultimo].distancia);
   
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
    novo_vertice = (vertice *)calloc(100000, sizeof(vertice));
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

void dfs(vertice *vertices , int x, int distancia,int *ultimo, int ver_visit){
    registro * aux;
    vertices[x].distancia = distancia;
    if(vertices[x].visitado == ver_visit){
        return;
    }
    printf("x:%d\n",x);
    printf("ultimo:%d\n",*ultimo);
    if(vertices[(*ultimo)].distancia < vertices[x].distancia)
        (*ultimo) = x;

    vertices[x].visitado = ver_visit;

    if (vertices[x].lista_adj==NULL)
        return;
        
    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL){
        if (vertices[aux->valor].visitado != ver_visit){
            dfs(vertices,aux->valor,distancia+1,ultimo,ver_visit); 
        }
        aux = aux->prox;
    }
}