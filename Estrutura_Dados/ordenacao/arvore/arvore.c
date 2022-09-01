#include <stdio.h>
#include <stdlib.h>

typedef struct arvore
{
    int qtd_elementos;
    struct no *raiz;
} arvore;

typedef struct no
{
    int valor;
    int qtd;
    struct no *esquerda;
    struct no *direita;
} no;

int primo(int num);
arvore *aloca_arvore();
no *aloca_no();
void incluir(arvore *a, int x);
void mostrar_pre_ordem(no * a,int *qtd_p);


int main()
{
    arvore *a1;
    int qtd_primo = 0;
    a1 = aloca_arvore();
    

    int procurado = 32;

    printf("\n Pre ordem: ");
    mostrar_pre_ordem(a1->raiz, &qtd_primo);
    

    printf("|%d|",qtd_primo);

    if (buscar(a1->raiz,procurado))
        printf("\n Numero %d esta na arvore",procurado);
    else
        printf("\n Numero %d nao esta na arvore",procurado);


    printf("\n");
    return 0;
}

arvore *aloca_arvore()
{
    arvore *nova;
    nova = (arvore *)calloc(1, sizeof(arvore));
    return nova;
}

no *aloca_no()
{
    no *novo;
    novo = (no *)calloc(1, sizeof(no));
    return novo;
}

void incluir(arvore *a, int x)
{
    no *novo, *aux;
    novo = aloca_no();
    novo->valor = x;
    novo->qtd = 1;

    int inseriu = 0;

    if (a->raiz == NULL)
    {
        a->raiz = novo;
        a->qtd_elementos++;
    }
    else
    {
        aux = a->raiz;
        while (!inseriu)
        {
            if (aux->valor == x)
            {
                aux->qtd++;
                return;
            }
            else
            {
                if (x < aux->valor)
                {
                    if (aux->esquerda == NULL)
                    {
                        aux->esquerda = novo;
                        inseriu = 1;
                        a->qtd_elementos++;
                    }
                    else
                    {
                        aux = aux->esquerda;
                    }
                }
                else
                {
                    if (aux->direita==NULL)
                    {
                        aux->direita = novo;
                        inseriu=1;
                        a->qtd_elementos++;
                    }
                    else
                    {
                        aux = aux->direita;
                    }
                }
            }
        }
    }
}

void mostrar_pre_ordem(no * a,int *qtd_p)
{
    if (a==NULL)
        return;
    
    *qtd_p = *qtd_p + primo(a->valor);
    mostrar_pre_ordem(a->esquerda,qtd_p);
    mostrar_pre_ordem(a->direita,qtd_p);
}


int primo(int num){

    if(num == 0 || num == 1){
        return 0;
    }else{
        for(int i = 2; i < num; i++){
            if(num%i == 0){
                return 0;
            }
        }
    }
    return 1;
}