#include <stdio.h>
#include <stdlib.h>
//n^2 - prim
//n log n - kruskal
//O(1) - remover min heap
//O(log n) - inserir min heap

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
    struct par lista_adj[100];
    int tam_lista_adj;
    int pai;
    int alterado;
}vertice;

registro *aloca_registro();
lista *aloca_lista();
void incluir_lista(lista *l, int vertice_1,int vertice_2,int distancia);
void mostrar_lista(lista *l);
trio remover(lista *l);
int empty(lista *l);
void mostrar(vertice *vertices, int qtd_vertices);

int main(){

    int count = 0;
    int qtd_vertices, qtd_arestas,par_1,par_2,peso;
    vertice * vertices;
    trio t;
    par p;
    lista *l;

    l = aloca_lista();

    printf("\nDigite a quantidade de Vertices e Arestas: ");
    scanf("%d %d",&qtd_vertices, &qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0;i<qtd_arestas;i++){
        printf("\nDigite os vertices ligados e o seu peso: ");
        scanf("%d %d %d",&par_1,&par_2,&peso);
        
        incluir_lista(l,par_1,par_2,peso);
    }

    mostrar_lista(l);

    while(count < (qtd_vertices-1) || !empty(l)){
        t = remover(l);
        
        //Verifico se eles já foram adicionados
        if(vertices[t.vertice_1].pai == 0)
            vertices[t.vertice_1].pai = t.vertice_1;
        if(vertices[t.vertice_2_distancia.vertice].pai == 0)
            vertices[t.vertice_2_distancia.vertice].pai = t.vertice_2_distancia.vertice;

        //Verifico se existe o ciclo
        if(vertices[t.vertice_1].pai != vertices[t.vertice_2_distancia.vertice].pai){
            if(!vertices[t.vertice_2_distancia.vertice].alterado){
                vertices[t.vertice_2_distancia.vertice].pai = vertices[t.vertice_1].pai;
                vertices[t.vertice_2_distancia.vertice].alterado = 1;
            }else if(!vertices[t.vertice_1].alterado){
                vertices[t.vertice_1].pai = vertices[t.vertice_2_distancia.vertice].pai;
                vertices[t.vertice_1].alterado = 1;
            }
            p.distancia = t.vertice_2_distancia.distancia;

            p.vertice = t.vertice_2_distancia.vertice;
            vertices[t.vertice_1].lista_adj[vertices[t.vertice_1].tam_lista_adj] = p;
            vertices[t.vertice_1].tam_lista_adj++;

            p.vertice = t.vertice_1;
            vertices[t.vertice_2_distancia.vertice].lista_adj[vertices[t.vertice_2_distancia.vertice].tam_lista_adj] = p;
            vertices[t.vertice_2_distancia.vertice].tam_lista_adj++;
            count++;
        }else{
            printf("\nCiclo entre %d e %d\n",t.vertice_1,t.vertice_2_distancia.vertice);
        }
    }

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

void mostrar_lista(lista *l){

    registro *aux;

    aux = l->inicio;
    while (aux != NULL){
        printf("(%d %d |%d|)\n", aux->t.vertice_1,aux->t.vertice_2_distancia.vertice,aux->t.vertice_2_distancia.distancia);
        aux = aux->prox;
    }
    printf("\n");
}

void mostrar(vertice *vertices, int qtd_vertices){
    for(int i=1;i<=qtd_vertices; i++){
        printf("\n|Vertice %d:",i);
        for(int j = 0;j<vertices[i].tam_lista_adj;j++){
            printf(" -> %d",vertices[i].lista_adj[j]);
        }
        printf("|");
    }
}
