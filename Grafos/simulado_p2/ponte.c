#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int lista_adj[100000];
    int tam_lista_adj;
    int in;
    int lower;
}vertice;

int count = 1;

int menor(int a, int b) ;
void ponte(vertice * vertices, int qtd_vertices, int raiz, int pai);

int main()
{
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

    ponte(vertices,qtd_vertices,1,1);
    return 0;
}

void ponte(vertice * vertices, int qtd_vertices, int raiz, int pai)
{
    int filho;

    vertices[raiz].visitado = 1;
    vertices[raiz].in = count;
    vertices[raiz].lower = count;
    count++;

    for(int i=0;i<vertices[raiz].tam_lista_adj;i++){
        filho = vertices[raiz].lista_adj[i];
        if (filho != pai){
            if (vertices[filho].visitado == 1){
                vertices[raiz].lower = menor(vertices[raiz].lower,vertices[filho].in);
            }else{
                ponte(vertices,qtd_vertices,filho,raiz);
                if (vertices[filho].lower > vertices[raiz].in){
                    printf("\nA estrada de que conecta a cidade %d e %d nao pode entrar em reforma.\n", raiz, filho);
                }
                vertices[raiz].lower = menor(vertices[raiz].lower, vertices[filho].lower);
            }
        }
    }
}


int menor(int a, int b) { return a<b ? a : b;}