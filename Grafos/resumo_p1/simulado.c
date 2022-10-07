#include <stdio.h>
#include <stdlib.h>

typedef struct vertices {

    int visitado;
    int lista_adj[9999];
    int tam_lista_adj;
    int distancia;
}vertice;

void mostrar_saidas(int *saidas, int qtd_consultas);
void dfs(vertice *vertices , int qtd_vertices, int raiz,int distancia,int verificador);

int main(){

    int qtd_vertices, qtd_arestas,par_1,par_2,qtd_consultas;
    int *saidas;
    vertice * vertices;
    scanf("%d\n%d",&qtd_vertices, &qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0;i<qtd_arestas;i++){
        scanf("%d %d",&par_1,&par_2);

        vertices[par_1].lista_adj[vertices[par_1].tam_lista_adj] = par_2;
        vertices[par_1].tam_lista_adj++;

        vertices[par_2].lista_adj[vertices[par_2].tam_lista_adj] = par_1;
        vertices[par_2].tam_lista_adj++;
    }

    scanf("%d",&qtd_consultas);

    saidas = (int*)calloc(qtd_consultas, sizeof(int));

    for(int i = 0; i < qtd_consultas;i++){
        scanf("%d %d",&par_1,&par_2);
        dfs(vertices,qtd_vertices,par_1,0,i+1);
        saidas[i] = vertices[par_2].distancia;
    }

    mostrar_saidas(saidas,qtd_consultas);

    return 0;
}

void dfs(vertice *vertices , int qtd_vertices, int raiz,int distancia,int verificador){
    if(vertices[raiz].visitado == verificador)
        return;

    vertices[raiz].visitado = verificador;
    vertices[raiz].distancia = distancia;

    for(int i=0;i<vertices[raiz].tam_lista_adj;i++){
        if (vertices[vertices[raiz].lista_adj[i]].visitado != verificador){
            dfs(vertices,qtd_vertices,vertices[raiz].lista_adj[i],distancia+1,verificador);
        }
    }
}

void mostrar_saidas(int *saidas, int qtd_consultas){
    for(int i = 0; i < qtd_consultas; i++){
        printf("\n%d",saidas[i]);
    }
}