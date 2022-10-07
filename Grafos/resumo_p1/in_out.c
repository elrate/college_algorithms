#include <stdio.h>
#include <stdlib.h>

int valor = 1;

typedef struct vertices {
    int lista_adj[100];
    int tam_lista_adj;
    int visitado;
    int in;
    int out;
}vertice;

void mostrar_lista(vertice *vertices, int qtd_vertices);
void dfs(vertice *vertices , int qtd_vertices, int raiz);

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

    dfs(vertices,qtd_vertices,1);

    mostrar_lista(vertices,qtd_vertices);

    scanf("\n%d %d", &par_1,&par_2);

    //in < out && out > in
    if(vertices[par_1].in < vertices[par_2].out && vertices[par_1].out > vertices[par_2].in)
        printf("\nSim");
    else   
        printf("\nNao");
    return 0;
}

void mostrar_lista(vertice *vertices, int qtd_vertices){
    for(int i=1;i<=qtd_vertices; i++){
        printf("\n|Vertice %d: In: %d Out: %d",i,vertices[i].in,vertices[i].out);
        for(int j = 0;j<vertices[i].tam_lista_adj;j++){
            printf(" -> %d",vertices[i].lista_adj[j]);
        }
        printf("|");
    }
}


void dfs(vertice *vertices , int qtd_vertices, int raiz){

    if(vertices[raiz].visitado == 1)
        return;

    vertices[raiz].visitado = 1;
    vertices[raiz].in = valor;
    valor++;

    for(int i = 0; i < vertices[raiz].tam_lista_adj; i++){
        if(vertices[vertices[raiz].lista_adj[i]].visitado == 0){
            dfs(vertices,qtd_vertices,vertices[raiz].lista_adj[i]);
        }
    }
    vertices[raiz].out = valor;
    valor++;
}