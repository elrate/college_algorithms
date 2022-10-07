#include <stdio.h>
#include <stdlib.h>

typedef struct vertices {
    int lista_adj[100];
    int tam_lista_adj;
}vertice;

void mostrar_lista(vertice *vertices, int qtd_vertices);

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

    mostrar_lista(vertices,qtd_vertices);
    return 0;
}

void mostrar_lista(vertice *vertices, int qtd_vertices){
    for(int i=1;i<=qtd_vertices; i++){
        printf("\n|Vertice %d: ",i);
        for(int j = 0;j<vertices[i].tam_lista_adj;j++){
            printf(" -> %d",vertices[i].lista_adj[j]);
        }
        printf("|");
    }
}


void dfs(vertice *vertices , int qtd_vertices, int raiz,int distancia){

    if(vertices[raiz].visitado == 0)
        return;

    vertices[raiz].distancia = distancia;
    vertices[raiz].visitado = 1;

    for(int i = 0; i < vertices[raiz].tam_lista_adj; i++){
        if(vertices[vertices[raiz].lista_adj[i]].visitado == 0){
            dfs(vertices,qtd_vertices,vertices[raiz].lista_adj[i],distancia+1);
        }
    }
}