#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int visitado;
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
void dfs(vertice *vertices , int x,int pai,int *verificador);

int main(){

    int qtd_vertices;
    int qtd_arestas;
    int cenarios;
    vertice *vertices;
    int par_2 = 0;
    int par_1 = 0;
    int verificador = 1;

    scanf("%d",&cenarios);

    for(int i = 0; i < cenarios;i++){
        scanf("%d %d",&qtd_vertices,&qtd_arestas);

        vertices = aloca_vertice();

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

        for(int i = 1;i <= qtd_vertices && verificador == 1;i++){
            if(vertices[i].visitado == 0)
                dfs(vertices,i,i,&verificador);
        }

        printf("Scenario #%d:\n",i+1);
        if(verificador == 1)
            printf("No suspicious bugs found!\n");
        else
            printf("Suspicious bugs found!\n");

        free(vertices);
        verificador = 1;
    }
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

void dfs(vertice *vertices , int x,int pai,int *verificador){
    registro * aux;
    
    if(vertices[x].visitado == 1){
        return;
    }
    if((*verificador) == 0)
        return;
        
    vertices[x].visitado = 1;

    if (vertices[x].lista_adj==NULL)
        return;
        
    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL){
        if (vertices[aux->valor].visitado==0){
            dfs(vertices,aux->valor,x,verificador); 
        }else if(aux->valor != pai){
            (*verificador) = 0;
            return;
        }
        aux = aux->prox;
    }
}