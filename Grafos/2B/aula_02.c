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
    struct par lista_adj[100];
    int tam_lista_adj;
    int distancia;
}vertice;

registro *aloca_registro();
lista *aloca_lista();
void incluir_lista(lista *l, int vertice,int distancia);
void mostrar_lista(lista *l);
par remover(lista *l);
int empty(lista *l);
void mostrar_grafo(vertice *vertices, int qtd_vertices);
void dijkstra(vertice * vertices, int raiz);

int main(){

    int infinito = 10000;
    int qtd_vertices, qtd_arestas,par_1,par_2,peso,raiz;
    vertice * vertices;
    par p;

    printf("\nDigite a quantidade de Vertices e Arestas: ");
    scanf("%d %d",&qtd_vertices, &qtd_arestas);

    vertices = (vertice*)calloc(qtd_vertices+1,sizeof(vertice));

    for(int i = 0;i<qtd_arestas;i++){
        printf("\nDigite os vertices ligados e o seu peso: ");
        scanf("%d %d %d",&par_1,&par_2,&peso);
        p.distancia = peso;

        p.vertice = par_2;
        vertices[par_1].lista_adj[vertices[par_1].tam_lista_adj] = p;
        vertices[par_1].distancia = infinito;
        vertices[par_1].tam_lista_adj++;

        p.vertice = par_1;
        vertices[par_2].lista_adj[vertices[par_2].tam_lista_adj] = p;
        vertices[par_2].distancia = infinito;
        vertices[par_2].tam_lista_adj++;
    }

    printf("\nDigite a raiz do dijkstra: ");
    scanf("%d",&raiz);

    printf("\nGrafo antes do dijkstra:");
    mostrar_grafo(vertices,qtd_vertices);

    dijkstra(vertices,raiz);

    printf("\n\nGrafo depois do dijkstra:");
    mostrar_grafo(vertices,qtd_vertices);

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

void mostrar_grafo(vertice *vertices, int qtd_vertices){
    for(int i=1;i<=qtd_vertices; i++){
        printf("\nVertice %d: Distancia: %d -> ",i,vertices[i].distancia);
        for(int j = 0;j<vertices[i].tam_lista_adj;j++){
            printf("| Vertice: %d Peso: %d ",vertices[i].lista_adj[j].vertice,vertices[i].lista_adj[j].distancia);
        }
        printf("|");
    }
}

void dijkstra(vertice * vertices, int raiz){

    lista *l;
    par ret;
    int soma_distancia_peso,valor,distancia;

    l = aloca_lista();

    vertices[raiz].distancia = 0;

    //Inclui na fila de memoria
    incluir_lista(l,raiz,0);

    while(!empty(l)){
        //Retira da fila o primeiro registro (menor distancia)
        ret = remover(l);
        for(int i = 0; i < vertices[ret.vertice].tam_lista_adj; i++){

            //Calcula a distancia entre um vertice e o outro
            soma_distancia_peso = ret.distancia + vertices[ret.vertice].lista_adj[i].distancia;
            //Salva o valor do vertice da iteracao da lista adjacente
            valor = vertices[ret.vertice].lista_adj[i].vertice;

            //Verifica se a distancia nova e menor que a atual
            if(soma_distancia_peso < vertices[valor].distancia){
                //Se for ele atualiza, e coloca na fila
                vertices[valor].distancia = soma_distancia_peso;
                incluir_lista(l,valor,soma_distancia_peso);
            }
            
        }
    }

}