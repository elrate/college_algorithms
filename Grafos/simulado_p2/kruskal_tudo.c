#include <stdio.h>
#include <stdlib.h>

typedef struct par{
    int vertice;
    int distancia;
}par;

typedef struct trio{
    int vertice_1;
    struct par vertice_2_distancia;
}trio;

typedef struct lista
{
    int qtd;
    struct registro *inicio;
} lista;

typedef struct registro
{
    struct trio t;
    struct registro *prox;
} registro;

typedef struct vertices {
    struct par lista_adj[1000000];
    int tam_lista_adj;
    int pai;
    int alterado;
}vertice;

registro *aloca_registro();
lista *aloca_lista();
void matriz_lista(lista *l,int **mat,int qtd_vertices);
void incluir_lista(lista *l, int vertice_1,int vertice_2,int distancia);
trio remover(lista *l);
int empty(lista *l);
void mostrar(vertice *vertices, int qtd_vertices);
void kruskal(vertice *v,lista *l,int qtd_vertices);
void caso_recebe_matriz(int **mat, int qtd_vertices);
void caso_matriz_pronta(int **mat);
void inserir_vertice(vertice *vertices, trio t);

int main(){

    int qtd_vertices, qtd_arestas;
    int **mat;
    vertice *vertices;
    lista *l;

    l = aloca_lista();

    scanf("%d %d",&qtd_vertices, &qtd_arestas);

    //qtd_vertices = 6;
    //qtd_arestas = 14;

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));
    mat = (int**)calloc(qtd_vertices+1,sizeof(int*));

    for(int i=0;i<qtd_vertices+1;i++)
        mat[i] = (int*)calloc(qtd_vertices+1,sizeof(int));

    //caso_matriz_pronta(mat);
    caso_recebe_matriz(mat,qtd_vertices);

    matriz_lista(l,mat,qtd_vertices);

    kruskal(vertices,l,qtd_vertices);

    mostrar(vertices,qtd_vertices);

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

void incluir_lista(lista *l, int vertice_1,int vertice_2,int distancia){
    
    if (l == NULL)
        return;

    registro *novo, *aux = NULL, *ant = NULL;
    
    novo = aloca_registro();
    novo->t.vertice_1 = vertice_1;
    novo->t.vertice_2_distancia.vertice = vertice_2;
    novo->t.vertice_2_distancia.distancia = distancia;

    if (l->inicio == NULL)
        l->inicio = novo;
    else{
        int inserido = 0;
        aux = l->inicio;
        while (aux != NULL && !inserido){
            if (aux->t.vertice_2_distancia.distancia < novo->t.vertice_2_distancia.distancia){
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

trio remover(lista *l){
    trio trio_removido;

    if(l->inicio == NULL){
        trio_removido.vertice_1 = -1;
        trio_removido.vertice_2_distancia.vertice = -1;
        trio_removido.vertice_2_distancia.distancia = -1;
    }else{
        registro *aux;

        aux = l->inicio;
        l->inicio = aux->prox;

        trio_removido.vertice_1 = aux->t.vertice_1;
        trio_removido.vertice_2_distancia.vertice = aux->t.vertice_2_distancia.vertice;
        trio_removido.vertice_2_distancia.distancia = aux->t.vertice_2_distancia.distancia;

        l->qtd--;
        free(aux);
    }

    return trio_removido;
}

int empty(lista *l){
    if(l->qtd == 0)
        return 1;
    return 0;
}

void mostrar(vertice *vertices, int qtd_vertices){
    printf("\n{");
    for(int i=1;i<=qtd_vertices; i++){
        for(int j = 0;j<vertices[i].tam_lista_adj;j++)
            printf("(%d,%d)",i,vertices[i].lista_adj[j].vertice);
    }
    printf("}\n");
}

void matriz_lista(lista *l,int **mat,int qtd_vertices){
    for(int i = 1;i<=qtd_vertices;i++){
        for(int j = i+1;j<=qtd_vertices;j++){
            if(mat[i][j] != 0)
                incluir_lista(l,i,j,mat[i][j]);
        }
    }
}

void kruskal(vertice *vertices,lista *l,int qtd_vertices){
    int count = 0;
    trio t;

    while(count < (qtd_vertices-1) && !empty(l)){
        t = remover(l);
        
        if(vertices[t.vertice_1].pai == 0)
            vertices[t.vertice_1].pai = t.vertice_1;
        if(vertices[t.vertice_2_distancia.vertice].pai == 0)
            vertices[t.vertice_2_distancia.vertice].pai = t.vertice_2_distancia.vertice;

        if(vertices[t.vertice_1].pai != vertices[t.vertice_2_distancia.vertice].pai){
            if(!vertices[t.vertice_2_distancia.vertice].alterado)
                vertices[t.vertice_2_distancia.vertice].pai = vertices[t.vertice_1].pai;
            else if(!vertices[t.vertice_1].alterado)
                vertices[t.vertice_1].pai = vertices[t.vertice_2_distancia.vertice].pai;
        
            vertices[t.vertice_2_distancia.vertice].alterado = 1;
            vertices[t.vertice_1].alterado = 1;

            inserir_vertice(vertices, t);

            count++;
        }
    }
}

void inserir_vertice(vertice *vertices, trio t){
    par p;

    p.distancia = t.vertice_2_distancia.distancia;

    p.vertice = t.vertice_2_distancia.vertice;
    vertices[t.vertice_1].lista_adj[vertices[t.vertice_1].tam_lista_adj] = p;
    vertices[t.vertice_1].tam_lista_adj++;

    p.vertice = t.vertice_1;
    vertices[t.vertice_2_distancia.vertice].lista_adj[vertices[t.vertice_2_distancia.vertice].tam_lista_adj] = p;
    vertices[t.vertice_2_distancia.vertice].tam_lista_adj++;
}

void caso_recebe_matriz(int **mat, int qtd_vertices){

    for(int i = 1;i<=qtd_vertices;i++){
        for(int j = 1;j<=qtd_vertices;j++){
            scanf("%d",&mat[i][j]);
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