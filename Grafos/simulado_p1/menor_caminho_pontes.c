#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
    int distancia;
    struct lista *lista_adj;
} vertice;

typedef struct fila{
    int tamanho;
    struct registro *inicio;
    struct registro *fim;
}fila;

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

fila* aloca_fila();
void insert(fila *f,int valor);
int remover(fila *f);
int empty(fila *f);
registro *aloca_registro();
lista *aloca_lista();
vertice *aloca_vertice();
void incluir_lista(lista *l, int x);
void bfs(vertice *vertices, int raiz);

int main(int *argc, char *argv[])
{
    int qtd_vertices, qtd_arestas, par_1, par_2, qtd_testes;
    vertice *vertices;
    int *vetor_result;

    vetor_result = (int*)malloc(sizeof(int));

    scanf("%d", &qtd_testes);

    for(int i = 0; i < qtd_testes;i++){
        vertices = aloca_vertice();
        scanf("%d %d",&qtd_vertices, &qtd_arestas);

        for(int i = 0; i < (qtd_arestas);i++){

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
        bfs(vertices,1);
        vetor_result[i] = vertices[qtd_vertices].distancia;
        free(vertices);
    }
    for(int i = 0; i < qtd_testes;i++){
        printf("\n%d",vetor_result[i]);
    }
    printf("\n");
    return 0;
}

fila* aloca_fila(){
    fila *novo;
    novo = (fila*) malloc(sizeof(fila));
    novo->tamanho = 0;
    novo->inicio = NULL;
    novo->fim = NULL;
    return novo;
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

vertice *aloca_vertice(){
    vertice *novo_vertice;
    novo_vertice = (vertice *)calloc(1000, sizeof(vertice));
    return novo_vertice;
}

void insert(fila *f,int valor){

    registro *novo;
    novo = aloca_registro();
    novo->valor = valor;

    if(empty(f)){
        f->inicio = novo;
    }else{
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tamanho++;
}

int remover(fila *f){

    if(empty(f)){
        return -1;
    }else{
        registro *aux;
        int num_removido;

        aux = f->inicio;
        f->inicio = aux->prox;
        num_removido = aux->valor;

        if(aux->prox == NULL){
            f->fim = NULL; 
        }

        f->tamanho--;
        free(aux);
        return num_removido;
    }
}

int empty(fila *f){

    if(f->inicio == NULL && f->fim == NULL){
        return 1;
    }else{
        return 0;
    } 
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

void bfs(vertice *vertices, int raiz){
    fila *f;
    registro *aux;
    f = aloca_fila();
    int ret;

    vertices[raiz].distancia = 0;
    vertices[raiz].visitado = 1;

    insert(f,raiz);

    while(!empty(f)){
        ret = remover(f);
        aux = vertices[ret].lista_adj->inicio;
    
        while(aux != NULL){
            if(vertices[aux->valor].visitado == 0){
                vertices[aux->valor].visitado = 1;
                vertices[aux->valor].distancia = vertices[ret].distancia+1;
                insert(f,aux->valor);
            }
            aux = aux->prox;
        }
    }
}