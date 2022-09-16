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
void mostrar_lista(lista *l);
void dfs(vertice *vertices , int x,unsigned long long *comb);

int main(){

    int casos_teste;
    unsigned long long *qtd_lideres;
    int qtd_arestas;
    int qtd_vertices;
    vertice *vertices;
    int par_2 = 0;
    int par_1 = 0;
    unsigned long long count,total_comb,comb;

    scanf("%d",&casos_teste);
    while((casos_teste > 0)){

        scanf("%d %d", &qtd_vertices,&qtd_arestas);

        qtd_lideres = (unsigned long long *)calloc(qtd_vertices, sizeof(unsigned long long));

        vertices = aloca_vertice();

        for(int i = 0; i < qtd_arestas;i++){

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
        
        count = 0;
        comb = 0;
        for(int i = 1;i <= qtd_vertices;i++){
            if(vertices[i].visitado == 0){
                dfs(vertices,i,&comb);
                qtd_lideres[count] = comb;
                count++;
                comb = 0;
            }
        }
        total_comb = 1;
        for(int i = 0;i<count;i++){
            total_comb = total_comb * qtd_lideres[i];
            total_comb = total_comb % 1000000007;
        }
        printf("%llu %llu\n",count, total_comb);
        free(qtd_lideres);
        free(vertices);
        casos_teste--;
    }
    
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

vertice *aloca_vertice(){
    vertice *novo_vertice;
    novo_vertice = (vertice *)calloc(1000000, sizeof(vertice));
    return novo_vertice;
}

void incluir_lista(lista *l, int x){
    
    if (l == NULL)
        return;

    registro *novo, *aux = NULL, *ant = NULL;
    novo = aloca_registro();
    novo->valor = x;

    if (l->inicio == NULL)
    {
        l->inicio = novo;
    }
    else
    {
        int inserido = 0;
        aux = l->inicio;
        while (aux != NULL && !inserido)
        {

            if (aux->valor == novo->valor)
            {
                return;
            }

            if (aux->valor < novo->valor)
            {
                ant = aux;
                aux = aux->prox;
            }
            else
            {
                if (ant == NULL)
                    l->inicio = novo;
                else
                    ant->prox = novo;

                novo->prox = aux;
                inserido = 1;
            }
        }
        if (!inserido)
        {
            ant->prox = novo;
            inserido = 1;
        }
    }
    l->qtd++;
    return;
}


void mostrar_lista(lista *l){
    registro *aux;

    if (l == NULL){
        printf("\n Lista nula");
        return;
    }

    if (l->inicio == NULL){
        printf("\n Lista vazia");
        return;
    }

    aux = l->inicio;
    while (aux != NULL){
        printf(" -> %d", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

void dfs(vertice *vertices , int x,unsigned long long *comb)
{   
    registro * aux;
    if(vertices[x].visitado == 1){
        return;
    }
    (*comb)++;
        
    vertices[x].visitado = 1;

    if (vertices[x].lista_adj==NULL)
        return;
        
    aux = vertices[x].lista_adj->inicio;

    while(aux!=NULL)
    {
        if (vertices[aux->valor].visitado==0)
        {
            dfs(vertices,aux->valor,comb); 
        }
        aux = aux->prox;
    }
}