#include <stdio.h>
#include <stdlib.h>

typedef struct par{
    int vertice;
    int distancia;
}par;
typedef struct lista
{
    int qtd;
    struct registro *inicio;
} lista;

typedef struct registro
{
    struct par p;
    struct registro *prox;
} registro;

typedef struct vertices {
    struct par lista_adj[1000000];
    int tam_lista_adj;
    int distancia;
}vertice;

registro *aloca_registro();
lista *aloca_lista();
void incluir_lista(lista *l, int vertice,int distancia);
void mostrar_lista(lista *l);
par remover(lista *l);
int empty(lista *l);
void mostrar_grafo(vertice *vertices, int qtd_vertices,int verificador);
void dijkstra(vertice * vertices, int raiz);
void matriz_grafo(int **mat,vertice *vertices,int qtd_vertices);
void caso_recebe_matriz(int **mat, int qtd_vertices);
void caso_matriz_pronta(int **mat);

int main(){

    int qtd_vertices, qtd_arestas;
    int **mat;
    vertice * vertices;

    scanf("%d %d",&qtd_vertices,&qtd_arestas);

    //qtd_vertices = 6;
    //qtd_arestas = 14;

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));
    mat = (int**)calloc(qtd_vertices+1,sizeof(int*));

    for(int i=0;i<qtd_vertices+1;i++)
        mat[i] = (int*)calloc(qtd_vertices+1,sizeof(int));

    //caso_matriz_pronta(mat);
    caso_recebe_matriz(mat,qtd_vertices);

    matriz_grafo(mat,vertices,qtd_vertices);

    dijkstra(vertices,qtd_vertices);

    mostrar_grafo(vertices,qtd_vertices,0);

    return 0;
}

lista *aloca_lista()
{
    lista *novo_lista;
    novo_lista = (lista *)calloc(1, sizeof(lista));
    return novo_lista;
}

registro *aloca_registro()
{
    registro *novo_registro;
    novo_registro = (registro *)calloc(1, sizeof(registro));
    return novo_registro;
}

void incluir_lista(lista *l, int vertice,int distancia){
    
    if (l == NULL)
        return;

    registro *novo, *aux = NULL, *ant = NULL;
    
    novo = aloca_registro();
    novo->p.vertice = vertice;
    novo->p.distancia = distancia;

    if (l->inicio == NULL)
        l->inicio = novo;
    else{
        int inserido = 0;
        aux = l->inicio;
        while (aux != NULL && !inserido){
            if (aux->p.distancia < novo->p.distancia){
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

par remover(lista *l){
    par par_removido;

    if(l->inicio == NULL){
        par_removido.vertice = -1;
        par_removido.distancia = -1;
    }else{
        registro *aux;

        aux = l->inicio;
        l->inicio = aux->prox;

        par_removido.vertice = aux->p.vertice;
        par_removido.distancia = aux->p.distancia;

        l->qtd--;
        free(aux);
    }

    return par_removido;
}

int empty(lista *l){
    if(l->qtd == 0)
        return 1;
    return 0;
}

void mostrar_lista(lista *l){

    registro *aux;

    aux = l->inicio;
    while (aux != NULL){
        printf("(%d %d)\n", aux->p.vertice,aux->p.distancia);
        aux = aux->prox;
    }
    printf("\n");
}

void mostrar_grafo(vertice *vertices, int qtd_vertices,int verificador){
    char alfabeto[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if(verificador){
        for(int i=1;i<=qtd_vertices; i++)
            printf("\nVertice: %c = %d",alfabeto[i-1],vertices[i].distancia);
    }else{
        for(int i=1;i<=qtd_vertices; i++)
            printf("\nVertice: %d = %d",i,vertices[i].distancia);
    }
}

void dijkstra(vertice * vertices, int raiz){

    lista *l;
    par ret;
    int soma_distancia_peso,valor,distancia;

    l = aloca_lista();

    vertices[raiz].distancia = 0;

    incluir_lista(l,raiz,0);

    while(!empty(l)){
        ret = remover(l);
        for(int i = 0; i < vertices[ret.vertice].tam_lista_adj; i++){

            soma_distancia_peso = ret.distancia + vertices[ret.vertice].lista_adj[i].distancia;
            valor = vertices[ret.vertice].lista_adj[i].vertice;

            if(soma_distancia_peso < vertices[valor].distancia){
                vertices[valor].distancia = soma_distancia_peso;
                incluir_lista(l,valor,soma_distancia_peso);
            }
            
        }
    }

}

void matriz_grafo(int **mat,vertice *vertices,int qtd_vertices){
    int infinito = 1000000;
    par p;
    for(int i = 1;i<=qtd_vertices;i++){
        for(int j = 1;j<=qtd_vertices;j++){
            if(mat[i][j] != 0){
                p.distancia = mat[i][j];

                p.vertice = j;
                vertices[i].lista_adj[vertices[i].tam_lista_adj] = p;
                vertices[i].distancia = infinito;
                vertices[i].tam_lista_adj++;

                p.vertice = i;
                vertices[j].lista_adj[vertices[j].tam_lista_adj] = p;
                vertices[j].distancia = infinito;
                vertices[j].tam_lista_adj++;
            }
        }   
    }
}

void caso_matriz_pronta(int **mat){
    for(int i = 0;i<=6; i++){
        for(int j = 0;j<=6;j++)
            mat[i][j] = 0;
    }

    mat[1][2] = 6;
    mat[1][3] = 9;
    mat[1][4] = 11;
    mat[1][5] = 5;
    mat[1][6] = 9;
    mat[2][3] = 3;
    mat[2][4] = 6;
    mat[2][5] = 5;
    mat[2][6] = 2;
    mat[3][4] = 0;
    mat[3][5] = 4;
    mat[3][6] = 4;
    mat[4][5] = 5;
    mat[4][6] = 6;
    mat[5][6] = 8;
}

void caso_recebe_matriz(int **mat, int qtd_vertices){

    for(int i = 1;i<=qtd_vertices;i++){
        for(int j = 1;j<=qtd_vertices;j++){
            scanf("%d",&mat[i][j]);
        }   
    }
}