#include <stdio.h>
#include <stdlib.h>

typedef struct vertices {
    int lista_adj[100];
    int tam_lista_adj;
    int visitado;
    int distancia;
}vertice;

typedef struct elemento{
    int valor;
    struct elemento *prox;
}elemento;

typedef struct fila{
    int tam;
    struct elemento *inicio;
    struct elemento *fim;
}fila;

void mostrar_lista(vertice *vertices, int qtd_vertices);
void bfs(vertice *vertices , int raiz);
int empty(fila *f);
void insert(fila *f,int valor);
int pop(fila *f);

int main(){

    int qtd_vertices, qtd_arestas;
    int par_1,par_2;
    vertice * vertices;
    scanf("%d %d",&qtd_vertices, &qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0;i<qtd_arestas;i++){
        scanf("%d %d",&par_1,&par_2);

        vertices[par_1].lista_adj[vertices[par_1].tam_lista_adj] = par_2;
        vertices[par_1].tam_lista_adj++;

        vertices[par_2].lista_adj[vertices[par_2].tam_lista_adj] = par_1;
        vertices[par_2].tam_lista_adj++;
    }

    bfs(vertices,1);
    mostrar_lista(vertices,qtd_vertices);
    return 0;
}

void mostrar_lista(vertice *vertices, int qtd_vertices){
    for(int i=1;i<=qtd_vertices; i++){
        printf("\n|Vertice %d: Distancia: %d ",i,vertices[i].distancia);
        for(int j = 0;j<vertices[i].tam_lista_adj;j++){
            printf(" -> %d",vertices[i].lista_adj[j]);
        }
        printf("|");
    }
}

int empty(fila *f){

    if(f->tam == 0)
        return 1;
    else
        return 0;
}

void insert(fila *f,int valor){

    elemento *aux;

    aux = (elemento*)calloc(1,sizeof(elemento));
    aux->valor = valor;

    if(f->tam == 0)
        f->inicio = aux;
    else
        f->fim->prox = aux;

    f->fim = aux;
    f->tam++;
}

int pop(fila *f){

    if(empty(f))
        return -1;
    else{
        int ret;
        ret = f->inicio->valor;
        f->inicio = f->inicio->prox;
        f->tam--;
        return ret;
    }
}


void bfs(vertice *vertices , int raiz){
    fila *f;
    int ret,proximo;

    f = (fila*)calloc(1,sizeof(fila));

    insert(f,raiz);

    while(!empty(f)){
        ret = pop(f);
        vertices[ret].visitado = 1;
        for(int i = 0; i < vertices[ret].tam_lista_adj;i++){
            proximo = vertices[ret].lista_adj[i];
            if(vertices[proximo].visitado == 0){
                vertices[proximo].distancia = vertices[ret].distancia+1;
                insert(f,proximo);
            }
        }
    }

}